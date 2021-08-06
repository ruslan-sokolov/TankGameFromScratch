#include "TankiAIController.h"

#include "Game/Game.h"

#include "Game/Gameplay/TankiGameMode.h"
#include "Game/Gameplay/TankiPlayerController.h"

#include "Game/Actors/PhoenixBaseActor.h"
#include "Game/Actors/TankActor.h"

namespace Game {
	
	float TankBrain::FireRate = GameConst::ENEMY_BASIC_FIRE_RATE;
	float TankBrain::ChangeDirectionTime = GameConst::ENEMY_AI_CHANGE_DIRECTION_RATE;

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
				// if tank collided -> change tank direction
				if (AITank->IsLastTimeCollisionPositive()) 
				{
					Direction NewDirection = GetRandomDirection();
					while (NewDirection == Brain.LastDirection)
						NewDirection = GetRandomDirection();

					AITank->MoveEnd(Brain.LastDirection);
					AITank->MoveBegin(NewDirection);

					Brain.LastDirection = NewDirection;
					Brain.TimeSinceDirectionChange = 0.f;
					Brain.TimeSinceLastCollide = 0.f;
					Brain.LastPositiveCollidedResult = std::move(AITank->GetLastCollisionResult());
				}

				// if tank moved too long in signle dir -> change tank dir
				if (Brain.TimeSinceDirectionChange >= Brain.ChangeDirectionTime)
				{
					AITank->MoveEnd(Brain.LastDirection);
					AITank->MoveBegin(GetRandomDirection());

					Brain.TimeSinceDirectionChange = 0.f;
				}

				// if tank shooted while ago -> shoot
				if (Brain.TimeSinceLastShot >= Brain.FireRate)
				{
					AITank->Fire();
					Brain.TimeSinceLastShot = 0.f;
				}
			}
		}
	}

	inline void TankiAIController::AddTank(Tank* EnemyTank)
	{
		if (EnemyTank)
		{
			TankBrains.push_back(EnemyTank);
		}
	}

	inline void TankiAIController::RemoveTank(Tank* EnemyTank)
	{
		if (EnemyTank)
		{
			auto It = std::find_if(TankBrains.begin(), TankBrains.end(), [&](const TankBrain& Brain) { return Brain.BrainOwner == EnemyTank; });
			if (It != TankBrains.end())
			{
				TankBrains.erase(It);
			}
		}
	}
}
