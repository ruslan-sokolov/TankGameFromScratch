#include "TankSpawnerActor.h"

#include <Engine/Utility/Math.h>

#include <Framework2D/Systems/SystemTimer.h>
#include <Framework2D/Gameplay/Level.h>

#include <Game/Game.h>

#include <Game/Gameplay/TankiAIController.h>

namespace Game {

	TankSpawner::TankSpawner(const std::string& Name, const Vec2& Position, 
		std::vector<TankSpawnPoint>&& SpawnPoints, std::vector<int>&& FlashyTankNums, 
		float SpawnRate, int TankToSpawnNumMax)
		: Actor(Name, Position), SpawnPoints(std::move(SpawnPoints)), FlashyTankNums(std::move(FlashyTankNums)),
		SpawnRate(SpawnRate), TankToSpawnNumMax(TankToSpawnNumMax), SpawnedTankNum(0), bIsActivated(false)
	{
	}

	void TankSpawner::OnDestroy()
	{
		RemoveTimer();
	}

	inline void TankSpawner::ResetSpawnTimer()
	{
		SystemTimer::SetTimer(TimerHandle_SpawnTank, TIMER_CALLBACK(TankSpawner::SpawnTank), SpawnRate);
	}

	inline void TankSpawner::RemoveTimer()
	{
		SystemTimer::RemoveTimer(TimerHandle_SpawnTank);
	}

	void TankSpawner::SetActivate(bool bActivate)
	{
		if (bActivate)
		{
			if (!EnemyAICon) // check if tank enemy ai controller is set
			{
				GAME_LOG(error, "TankSpawner::SetActivate() can't activate spawner, EnemyAICon is nullptr!! Please use TankSpawner::SetEnemyAIController() before activation!");
			}

			ResetSpawnTimer();
		}
		else
		{
			RemoveTimer();
		}

		bIsActivated = bActivate;
	}

	inline TankSpawnPoint& TankSpawner::GetRandSpawnPoint()
	{
		int RandIndex = Engine::RandIntMax(SpawnPoints.size());

		TankSpawnPoint& RandSpawnPoint = SpawnPoints[RandIndex];

		// debug
		GAME_LOG(info, "Rand Spawn Point {}", RandSpawnPoint.SpawnPosition);

		return RandSpawnPoint;
	}

	void TankSpawner::SpawnTank()
	{
		// todo: fix SystemTimer insertion and deletion during iteration

		ENGINE_ASSERT(GetLevel(), "TankSpawner::SpawnTank() Level is nullptr!");
		if (!GetLevel()) return;

		if (IsTankSpawnerExhausted())  // if work done -> destroy Spawner actor
		{
			// debug
			GAME_LOG(info, "TankSpawner WORK DONE!!!!!!");
			
			Destroy();
		}
		else
		{
			// spawn enemy tank
			auto SpawnedTank = Tank::SpawnBasicTank(GetLevel(), GetRandSpawnPoint(), TankType::EnemyTank);

			// add enemy tank to AI Controller
			if (EnemyAICon) EnemyAICon->AddTank(SpawnedTank);
		
			// check flashy tank, incr SpawnedTankNum
			for (auto& FlashyIndex : FlashyTankNums)
			{
				if (SpawnedTankNum == FlashyIndex)
				{
					SpawnedTank->bDropPickableOnDeath = true;
		
					// debug
					GAME_LOG(info, "TANKSPAWNER Flashy index used: {}", SpawnedTankNum - 1);
				}
			}

			// incr spawner tank num
			++SpawnedTankNum;
		
			// reset spawn timer
			ResetSpawnTimer();
		
			// debug
			GAME_LOG(info, "TANKSPAWNER SPAWNED num: {}", SpawnedTankNum);
		}
	}


	// static
	TankSpawner* TankSpawner::CreateBasicTankAISpawnerCorners(Level* Level)
	{
		ENGINE_ASSERT(Level, "TankSpawner::CreateBasicTankAISpawnerCorners(Level*) Level is nullptr!");
		if (!Level) return nullptr;
		
		std::vector<TankSpawnPoint> SpawnPoints{ 
			TankSpawnPoint::BottomLeftSpawnPoint, 
			TankSpawnPoint::BottomRightSpawnPoint,
			TankSpawnPoint::TopLeftSpawnPoint,
			TankSpawnPoint::TopRightSpawnPoint
		};

		std::vector<int> FlashyTankNums(GameConst::FLASHY_ARRAY_DEFAULT, 
			GameConst::FLASHY_ARRAY_DEFAULT + GameConst::FLASHY_ARRAY_DEFAULT_SIZE);

		auto Spawner = Level->SpawnActorFromClass<TankSpawner>("TankSpawnerCorners", 0, Anchor::TOP_LEFT,
			std::move(SpawnPoints), std::move(FlashyTankNums),
			GameConst::TANK_SPAWN_RATE_DEFAULT, GameConst::TANK_SPAWN_NUM_DEFAULT);

		return Spawner;
	}

	// static
	TankSpawner* TankSpawner::CreateBasicTankAISpawnerTop(Level* Level)
	{
		ENGINE_ASSERT(Level, "TankSpawner::CreateBasicTankAISpawnerCorners(Level*) Level is nullptr!");
		if (!Level) return nullptr;

		std::vector<TankSpawnPoint> SpawnPoints{
			TankSpawnPoint::TopLeftSpawnPoint,
			TankSpawnPoint::TopCenterSpawnPoint,
			TankSpawnPoint::TopRightSpawnPoint
		};

		std::vector<int> FlashyTankNums(GameConst::FLASHY_ARRAY_DEFAULT,
			GameConst::FLASHY_ARRAY_DEFAULT + GameConst::FLASHY_ARRAY_DEFAULT_SIZE);

		auto Spawner = Level->SpawnActorFromClass<TankSpawner>("TankSpawnerTop", 0, Anchor::TOP_LEFT,
			std::move(SpawnPoints), std::move(FlashyTankNums),
			GameConst::TANK_SPAWN_RATE_DEFAULT, GameConst::TANK_SPAWN_NUM_DEFAULT);

		return Spawner;
	}

}