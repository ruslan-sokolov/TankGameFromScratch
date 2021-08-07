#include "TankiAIController.h"

#include "Game/Gameplay/TankiGameMode.h"
#include "Game/Gameplay/TankiPlayerController.h"

#include "Game/Actors/PhoenixBaseActor.h"
#include "Game/Actors/TankActor.h"

namespace Game {

	TankiAIController::TankiAIController()
	{
		// resesrve tank brains slots
		TankBrains.reserve(GameConst::TANK_SPAWN_NUM_DEFAULT);
	}

	void TankiAIController::OnStart()
	{
		GM = dynamic_cast<TankiGameMode*>(GetGameMode());
	}

	void TankiAIController::OnTick(float DeltaTime)
	{
		UpdateTankBehavior(DeltaTime);
	}

	inline void TankiAIController::TankChangeDirection(TankBrain& Brain)
	{
		ENGINE_ASSERT(Brain.BrainOwner, "TankChangeDirection: TankBrain.BrainOwner == nullptr!!!");

		Direction NewDirection = GetRandDirectionFilter(Brain.LastDirection);

		Brain.BrainOwner->MoveEnd(Brain.LastDirection);
		Brain.BrainOwner->MoveBegin(NewDirection);

		Brain.LastDirection = NewDirection;
		Brain.TimeSinceDirectionChange = 0.f;
		Brain.SetRandChangeDirTime();
	}

	inline void TankiAIController::TankStop(TankBrain& Brain)
	{
		ENGINE_ASSERT(Brain.BrainOwner, "TankStop: TankBrain.BrainOwner == nullptr!!!");

		Brain.BrainOwner->MoveEnd(Brain.LastDirection);
		Brain.TimeSinceDirectionChange += Brain.ChangeDirectionTime * 0.1f * GetGame()->GetDeltaTime(); // adjustment
	}

	inline void TankiAIController::TankShoot(TankBrain& Brain)
	{
		ENGINE_ASSERT(Brain.BrainOwner, "TankStop: TankBrain.BrainOwner == nullptr!!!");

		Brain.BrainOwner->Fire();

		Brain.TimeSinceLastShot = 0.f;
		Brain.SetRandFireRate();
	}

	inline void TankiAIController::UpdateTankBehavior(float DeltaTime)
	{
		// todo: fix
		// Refresh collective brain
		// CollectiveBrain.PlayerBase = GM->GetLevelPhoenixBase();
		// if (auto PC = GM->GetCustomPlayerTankController())
		// 	CollectiveBrain.PlayerTank = PC->GetControlledTank();

		for (auto& Brain : TankBrains)
		{
			// Update tank action-events elapsed timers
			Brain.UpdateTimers(DeltaTime);

			if (Tank* AITank = Brain.BrainOwner)
			{
				// if tank collided -> stop
				if (AITank->IsLastTimeCollisionPositive()) 
				{
					Brain.TimeSinceLastCollide = 0.f;
					Brain.LastPositiveCollidedResult = std::move(AITank->GetLastCollisionResult());

					TankStop(Brain);
				}

				// if tank moved too long in signle dir -> change tank dir
				if (Brain.TimeSinceDirectionChange >= Brain.ChangeDirectionTime)
				{
					TankChangeDirection(Brain);
				}

				// if tank shooted while ago -> shoot
				if (Brain.TimeSinceLastShot >= Brain.FireRate)
				{
					TankShoot(Brain);
				}
			}
		}
	}
}
