#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>
#include <Framework2D/Structs/TimerHandle.h>

#include <Game/Actors/TankActor.h>


namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent ai tank spawner
	 * 
	 */
	class TankSpawner : public Framework2D::Actor
	{
	protected:
		std::vector<TankSpawnPoint> SpawnPoints;
		
		// todo
		std::vector<int> FlashyTankNums;  // flashy tanks -> tanks that can drop boosters on death

		float SpawnRate;

		int TankToSpawnNumMax;
		int SpawnedTankNum;

		bool bIsActivated;

		TimerHandle TimerHandle_SpawnTank;
		inline void ResetSpawnTimer();
		inline void RemoveTimer();

		inline TankSpawnPoint& GetRandSpawnPoint();
		
		// Delayed func to spawn tank
		void SpawnTank();

		// If we spawn enemy tank, we need add it to ai controller
		class TankiAIController* EnemyAICon = nullptr;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		TankSpawner(const std::string& Name, const Vec2& Position, 
			std::vector<TankSpawnPoint>&& SpawnPoints, std::vector<int>&& FlashyTankNums, 
			float SpawnRate,  int TankToSpawnNumMax);
		
		void OnDestroy() override;

		// Activate/Deactivate tank spawner
		void SetActivate(bool bActivate);

		bool IsActivated() const { return bIsActivated; }

		// true if Already spawned tank num > tank to spawn num
		bool IsTankSpawnerExhausted() { return SpawnedTankNum >= TankToSpawnNumMax; }

		int GetSpawnedTankNum() const { return SpawnedTankNum; }

		// use this before activation to add spawned enemy tanks to ai controller
		void SetEnemyAIController(class TankiAIController* AICon) { EnemyAICon = AICon; }

		static TankSpawner* CreateBasicTankAISpawnerCorners(Level* Level);
		static TankSpawner* CreateBasicTankAISpawnerTop(Level* Level);

	};

}

