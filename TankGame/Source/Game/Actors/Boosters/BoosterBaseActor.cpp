#include "BoosterBaseActor.h"

#include <Framework2D/Systems/SystemTimer.h>

namespace Game {

	BoosterBase::BoosterBase(const std::string& Name, const Vec2& Position, float BoostInterval, int BoostTickNumToExec)
		: Actor(Name, Position), BoostInterval(BoostInterval), BoostTickNumToExec(BoostTickNumToExec)
	{
	}

	void BoosterBase::OnDestroy()
	{
		SystemTimer::RemoveTimer(TimerHandle_BoostTick);
	}

	void BoosterBase::OnTickBoost()
	{
		++TicksProcessed;

		OnBoostTicked();
		
		if (TicksProcessed >= BoostTickNumToExec)
		{
			bIsBoostActive = false;

			OnExpired();

			// delete timer
			SystemTimer::RemoveTimer(TimerHandle_BoostTick);
		}
	}


	void BoosterBase::ActivateBoost(Actor* Activator, bool Reactivate)
	{
		if (IsPendingKill()) return;

		OnActivated(Activator);

		bIsBoostActive = true;

		if (Reactivate)
		{
			TicksProcessed = 0;
		}

		if (BoostInterval > 0.f)
		{
			SystemTimer::SetTimer(TimerHandle_BoostTick, TIMER_CALLBACK(BoosterBase::OnTickBoost), BoostInterval, true);
		}
		else
		{
			BoostTickNumToExec = 1;
			OnTickBoost();
		}
	}
}
