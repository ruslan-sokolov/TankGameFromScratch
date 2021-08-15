#include "TankiLevel_0.h"

#include <Game/Game.h>

#include <Game/Gameplay/TankiGameMode.h>

#include <Game/Gameplay/TankiAIController.h>

#include <Game/Actors/Blocks/BlockSolidActor.h>
#include <Game/Actors/Blocks/BlockModularActor.h>
#include <Game/Actors/PhoenixBaseActor.h>
#include <Game/Actors/TankSpawnerActor.h>

namespace Game {

	TankiLevel_0::TankiLevel_0()
	{
		using namespace GameConst;

		const Vec2 ChunkZero(GAME_AREA_OFFSET_W, GAME_AREA_OFFSET_H);
		const Vec2 ChunkOffset(GAME_CHUNK_W, GAME_CHUNK_H);
		const Vec2 ChunkOffset_X(GAME_CHUNK_W, 0);
		const Vec2 ChunkOffset_Y(0, GAME_CHUNK_H);
		const Vec2 ChunkLastOffset_X(GAME_AREA_H1, 0);
		const Vec2 ChunkLastOffset_Y(0, GAME_AREA_W1);
		const Vec2 BasePosition(GAME_AREA_MID_W, GAME_AREA_H1);

		// Level walls:
		{
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 0, 0b1111110000000000);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 3);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 4);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 0, 0b1111111111111100);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 3);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 4);
			
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 0);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 3);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 0);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 3);
			
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 0, 0b1111111111110011);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 3);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 4);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 0, 0b1111001100000000);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 3);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 4);
			
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 7);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 3);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkOffset_Y * 8 + ChunkLastOffset_X);
			BlockModular::SpawnModularBrickBlock(this, ChunkOffset_Y * 8 - ChunkOffset_X * 2 + ChunkLastOffset_X);
			BlockModular::SpawnModularBrickBlock(this, ChunkOffset_Y * 8 - ChunkOffset_X * 3 + ChunkLastOffset_X);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 5);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 7);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 5);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 7);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 5);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 7);

			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 10 + ChunkOffset_X * 5, 0b000000011111111);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 10 + ChunkOffset_X * 7, 0b000000011111111);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 6, 0b1111111100000000);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 6, 0b0000000011111111);
			
			// around base
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 7, 0b0011001100000000);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 6, 0b1111111100000000);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 5, 0b1100110000000000);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 7, 0b0011001100110011);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 5, 0b1100110011001100);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 8);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 9);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 10);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 8);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 9);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 10);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 8);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 9);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 10);
			
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 8);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 9);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 10);
		}

		PlayerSpawnPoint = TankSpawnPoint(BasePosition - ChunkOffset_X * 2, Direction::UP, Anchor::BOTTOM);
		SpawnPlayerTank();
		
		PhoenixBase::SpawnDefaultBase(this, BasePosition, Anchor::BOTTOM);
		EnemyTankSpawner = TankSpawner::CreateBasicTankAISpawnerCorners(this);
	}

	Tank* TankiLevel_0::SpawnPlayerTank()
	{
		PlayerTank = Tank::SpawnBasicTank(this, PlayerSpawnPoint, TankType::PlayerTank);
		return PlayerTank;
	}

	void TankiLevel_0::OnStart()
	{
		// todo: handle spawn collision
		if (auto GM = dynamic_cast<TankiGameMode*>(GetGameMode()))
		{
			if (auto AICon = GM->GetCustomAIController())
			{
				EnemyTankSpawner->SetEnemyAIController(AICon);
				EnemyTankSpawner->SetActivate(true);
				EnemyTankSpawner = nullptr;
			}
			else
			{
				GAME_LOG(error, "TankiLevel_0::OnStart() AI Controller in TankiGameMode is nullptr!!");
			}
		}
		else
		{
			GAME_LOG(error, "TankiLevel_0::OnStart() casting GameMode to TankiGameMode failed!!");
		}
	}
}