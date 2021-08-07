#include "TankiLevel_0.h"

#include <Game/Game.h>

#include <Game/Gameplay/TankiGameMode.h>

// debug
#include <Game/Gameplay/TankiAIController.h>

#include <Game/Actors/Blocks/BlockSolidActor.h>
#include <Game/Actors/Blocks/BlockModularActor.h>
#include <Game/Actors/PhoenixBaseActor.h>

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

		TankSpawnPoint PlayerSpawnPoint(BasePosition - ChunkOffset_X * 2, Direction::UP, Anchor::BOTTOM);

		// Level walls:
		{
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 0, 0b1100110011001100);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 1, 0b1111111111111111);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 2, 0b0011001100110011);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 3, 0b0101010101010101);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 4, 0b0000111100001111);

			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 0, 0b1011011011011010);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 1, 0b1010010110100101);
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


			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 0);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 1);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 2);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 3);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 4);

			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 0);
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

			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 6);

			// around base
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 7);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 6);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 5);

			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 7);
			BlockModular::SpawnModularBrickBlock(this, ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 5);
			//

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

		// Spawn player tank
		PlayerTank = Tank::SpawnBasicTank(this, PlayerSpawnPoint, TankType::PlayerTank);

		// todo: add player base
		PlayerBase = nullptr;
	}

	void TankiLevel_0::OnStart()
	{
		// debug, testing ai controller
		if (auto GM = dynamic_cast<TankiGameMode*>(GetGameMode()))
		{
			if (auto AICon = GM->GetCustomAIController())
			{
				auto Tank_0 = Tank::SpawnBasicTank(this, TankSpawnPoint::TopLeftSpawnPoint, TankType::EnemyTank);
				auto Tank_1 = Tank::SpawnBasicTank(this, TankSpawnPoint::TopCenterSpawnPoint, TankType::EnemyTank);
				auto Tank_2 = Tank::SpawnBasicTank(this, TankSpawnPoint::TopRightSpawnPoint, TankType::EnemyTank);

				AICon->AddTank(Tank_0);
				AICon->AddTank(Tank_1);
				AICon->AddTank(Tank_2);
			}
		}

	}

	void TankiLevel_0::OnTick(float DeltaTime)
	{
	}

}