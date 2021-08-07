#pragma once

#include <Engine/Utility/Math.h>

#include <Framework2D/Gameplay/Controllers/AIController.h>
#include <Framework2D/Structs/Collision.h>
#include <Framework2D/Structs/Direction.h>

#include "Game/Game.h"

#include <vector>

namespace Game {

	using namespace Framework2D;

	class Tank;
	class PhoenixBase;

	class TankiGameMode;
	
	/** Coordinate AI as team with same goal, also adds cheating to AI */
	struct TankCollectiveBrain
	{
		Tank* PlayerTank = nullptr;
		PhoenixBase* PlayerBase = nullptr;

		TankCollectiveBrain() {}
		TankCollectiveBrain(Tank* PlayerTank, PhoenixBase* PlayerBase) : PlayerTank(PlayerTank), PlayerBase(PlayerBase) {}
	};

	/** This struct used to simulate enemy tank memory and perception*/
	struct TankBrain
	{
		Tank* BrainOwner = nullptr;

		float TimeSinceLastShot = 0;
		float TimeSinceDirectionChange = 0;
		float TimeSinceLastCollide = 0;

		CollisionCheckResult LastPositiveCollidedResult;

		Direction LastDirection = GetRandomDirection();

		float FireRate;
		float ChangeDirectionTime;

		void UpdateTimers(float DeltaTime) {
			TimeSinceLastShot += DeltaTime;
			TimeSinceDirectionChange += DeltaTime;
			TimeSinceLastCollide += DeltaTime;
		}
		
		void SetRandFireRate()
		{
			FireRate = Engine::RandFloatRange(GameConst::ENEMY_BASIC_FIRE_RATE_MIN, GameConst::ENEMY_BASIC_FIRE_RATE_MAX);
		}

		void SetRandChangeDirTime()
		{
			ChangeDirectionTime = Engine::RandFloatRange(GameConst::ENEMY_AI_CHANGE_DIRECTION_RATE_MIN,
				GameConst::ENEMY_AI_CHANGE_DIRECTION_RATE_MAX);
		}

		TankBrain() { SetRandFireRate(); SetRandChangeDirTime(); }
		TankBrain(Tank* BrainOwner) : BrainOwner(BrainOwner) { SetRandFireRate(); SetRandChangeDirTime(); }

		// movable only
		TankBrain(const TankBrain&) = delete;
		TankBrain(TankBrain&&) = default;
		TankBrain& operator=(const TankBrain&) = delete;
		TankBrain& operator=(TankBrain&&) = default;
	};

	/*
	 * This class is used to controll tanks on level
	 * This class simulates each tank independent behavior 
	 * and also has common inelligance to help coordinate each independent tank actor
	 */
	class TankiAIController : public Framework2D::AIController
	{
		// todo: make smarter, utilize common brain

		TankiGameMode* GM = nullptr;

		TankCollectiveBrain CollectiveBrain;
		std::vector<TankBrain> TankBrains;

		/** Handle move direction change for tank with brain */
		inline void TankChangeDirection(TankBrain& Brain);

		/** TankBrain stops Tank movement */
		inline void TankStop(TankBrain& Brain);

		/** TankBrain force tank to shoot */
		inline void TankShoot(TankBrain& Brain);

		/** onTick Calcs Move() and Fire() for each Tank in TankBrains container */
		inline void UpdateTankBehavior(float DeltaTime);

	public:

		TankiAIController();

		virtual void OnStart() override;
		virtual void OnTick(float DeltaTime) override;

		/** Tanks will be spawned dynamically and added on fly */
		void AddTank(Tank* EnemyTank) 
		{ 
			if (EnemyTank) TankBrains.push_back(EnemyTank); 
		}

		void RemoveTank(Tank* EnemyTank)
		{
			if (!EnemyTank) return;
	
			auto It = std::find_if(TankBrains.begin(), TankBrains.end(), [&](const TankBrain& Brain) { return Brain.BrainOwner == EnemyTank; });
				
			if (It != TankBrains.end()) TankBrains.erase(It);
		}
	};

}
