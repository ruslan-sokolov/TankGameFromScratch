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

	inline void SystemTimer::RemoveTimer(TimerHandle& Handle)
	{
		if (Handle.IsValid())  // check if valid
		{
			// todo: make safe
			auto It = Timers.begin() + Handle.TimerIndex;
			Timers.erase(It);  // remove timer

			Handle.Invalidate(); // invalidate timer
		}
	}

	inline void SystemTimer::SetTimer(TimerHandle& InOutHandle, TimerCbFn&& Callback, float Rate, bool bLoop)
	{
		RemoveTimer(InOutHandle);

		TimerData NewTimer(bLoop, Rate, InOutHandle, std::move(Callback));
		AddTimer(std::move(NewTimer));

		InOutHandle = NewTimer.Handle;  // out updated valid handler;
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
