#include "PCH_Framework.h"
#include "SystemTimer.h"

namespace Framework2D {

	// Static
	std::vector<TimerData> SystemTimer::Timers;
	std::vector<TimerData> SystemTimer::TimersPushbackQueue;

	inline void SystemTimer::AddTimer(TimerData&& Data)
	{
		if (TimersPushbackQueue.size() % VecTimerDataExtend == 0)  // extend
			TimersPushbackQueue.reserve(TimersPushbackQueue.size() + VecTimerDataExtend);

		Data.Handle.TimerId = SystemTimer::TotalCreatedNum++;  // Set Unique Valid handler;
		
		TimersPushbackQueue.push_back(std::move(Data));
	}

	inline void SystemTimer::InsertNewTimers()
	{
		if (TimersPushbackQueue.size())
		{
			if (Timers.capacity() < TimersPushbackQueue.size() + VecTimerDataExtend)  // extend
			{
				Timers.reserve(Timers.size() + TimersPushbackQueue.size() + VecTimerDataExtend);
			}

			std::move(TimersPushbackQueue.begin(), TimersPushbackQueue.end(), std::back_inserter(Timers));
			TimersPushbackQueue.clear();
		}
	}

	inline TimerData* SystemTimer::FindTimer(const TimerHandle& InHandle)
	{
		for (auto& Timer : TimersPushbackQueue)
		{
			if (Timer.Handle == InHandle) return &Timer;
		}

		for (auto& Timer : Timers)
		{
			if (Timer.Handle == InHandle) return &Timer;
		}
		
		return nullptr;
	}

	inline void SystemTimer::RemoveTimer(TimerHandle& InOutHandle)
	{
		if (!InOutHandle.IsValid()) return;

		if (TimerData* Timer = FindTimer(InOutHandle))
		{
			Timer->Handle.Invalidate(); // Pending to remove Timer in next UpdateTimers cycle
			InOutHandle.Invalidate();  // out invalid handler
		}
	}

	inline void SystemTimer::SetTimer(TimerHandle& InOutHandle, TimerCbFn&& Callback, float Rate, bool bLoop)
	{
		RemoveTimer(InOutHandle);  // try remove old timer if exists

		TimerData NewTimer(bLoop, Rate, InOutHandle, std::move(Callback));
		AddTimer(std::move(NewTimer));

		InOutHandle = NewTimer.Handle;  // out updated valid handler;
	}

	inline void SystemTimer::RemoveAllTimers()
	{
		Timers.clear();
		TimersPushbackQueue.clear();
	}

	inline void SystemTimer::UpdateTimers(float DeltaTime)
	{
		// this allow as safely add new timers if they called in timers delayed funcs
		// so main loop will not invalidate it's iterators
		InsertNewTimers();

		// this loop handle delayedFuncs execution during iteration
		auto It_InvalidBegin = Timers.begin(); // after loop invalid Timers should be in [It_InvalidBegin, Timers.End) range
		for (auto It_Valid = It_InvalidBegin, It_End = Timers.end(); It_Valid != It_End; ++It_Valid)
		{
			It_Valid->Update(DeltaTime); // update timers if valid, call cb if timer elapsed;

			if (It_Valid->Handle.IsValid())
			{
				if (It_Valid != It_InvalidBegin)
				{
					*It_InvalidBegin = std::move(*It_Valid);
				}
				++It_InvalidBegin;
			}
		}
		Timers.erase(It_InvalidBegin, Timers.end());
	}
}
