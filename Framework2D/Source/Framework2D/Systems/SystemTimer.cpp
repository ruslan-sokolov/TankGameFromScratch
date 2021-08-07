#include "PCH_Framework.h"
#include "SystemTimer.h"

namespace Framework2D {

	// Static
	std::vector<TimerData> SystemTimer::Timers;

	inline void SystemTimer::AddTimer(TimerData&& Data)
	{
		if (Timers.size() % VecTimerDataExtend == 0)
			Timers.reserve(Timers.size() + VecTimerDataExtend);

		Data.Handle.TimerId = SystemTimer::TotalCreatedNum++;  // Set Unique Valid handler;
		
		Timers.push_back(std::move(Data));
	}

	inline TimerData* SystemTimer::FindTimer(const TimerHandle& InHandle)
	{
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
	}

	inline void SystemTimer::UpdateTimers(float DeltaTime)
	{
		using TimerIt = std::vector<TimerData>::iterator;

		TimerIt It_InvalidBegin = Timers.begin(); // after loop invalid Timers should be in [It_InvalidBegin, Timers.End) range
		for (TimerIt It_Valid = It_InvalidBegin, It_End = Timers.end(); It_Valid != It_End; ++It_Valid)
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
