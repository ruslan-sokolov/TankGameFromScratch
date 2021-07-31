#include "PCH_Framework.h"
#include "SystemTimer.h"

namespace Framework2D {

	// Static
	std::vector<TimerData> SystemTimer::Timers;

	inline void SystemTimer::AddTimer(TimerData&& Data)
	{
		if (Timers.size() % VecTimerDataExtend == 0)
			Timers.reserve(Timers.size() + VecTimerDataExtend);

		Data.Handle.TimerIndex = Timers.size();  // Set Valid handler;
		Timers.push_back(std::move(Data));
	}

	inline void SystemTimer::RemoveTimer(TimerHandle& InOutHandle)
	{
		if (InOutHandle.TimerIndex < Timers.size())  // check if valid
		{
			auto It = Timers.begin() + InOutHandle.TimerIndex;
			It->Handle.Invalidate();  // Pending to remove Timer in next UpdateTimers cycle
		}
		InOutHandle.Invalidate(); // invalidate timer
	}

	inline void SystemTimer::SetTimer(TimerHandle& InOutHandle, TimerCbFn&& Callback, float Rate, bool bLoop)
	{
		RemoveTimer(InOutHandle);

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
		auto It_InvalidBegin = Timers.begin(); // after loop invalid Timers should be in [It_InvalidBegin, Timers.End) range
		for (auto It_Valid = It_InvalidBegin, It_End = Timers.end(); It_Valid != It_End; ++It_Valid) // todo: fix bug
		{
			if (It_Valid->Handle.IsValid())
			{
				It_Valid->Update(DeltaTime); // update timers, call cb if timer elapsed;

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
