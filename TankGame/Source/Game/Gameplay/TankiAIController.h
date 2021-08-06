#pragma once

#include <Framework2D/Gameplay/Controllers/AIController.h>
#include <Framework2D/Structs/Collision.h>
#include <Framework2D/Structs/Direction.h>

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

		static float FireRate;
		static float ChangeDirectionTime;

		void UpdateTimers(float DeltaTime) {
			TimeSinceLastShot += DeltaTime;
			TimeSinceDirectionChange += DeltaTime;
			TimeSinceLastCollide += DeltaTime;
		}

		TankBrain() {}
		TankBrain(Tank* BrainOwner) : BrainOwner(BrainOwner) {}

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

	public:

		TankiAIController();

		virtual void OnStart() override;
		virtual void OnTick(float DeltaTime) override;

		/** onTick Calcs Move() and Fire() for each Tank in TankBrains container */
		inline void UpdateTankBehavior(float DeltaTime);

		/** Tanks will be spawned dynamically and added on fly */
		inline void AddTank(Tank* EnemyTank);

		inline void RemoveTank(Tank* EnemyTank);
	
	};

}
