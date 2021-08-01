#include "TankiLevel_0.h"

#include <Game/Actors/TankActor.h>
#include <Game/Actors/BrickSolidActor.h>

namespace Game {

	TankiLevel_0::TankiLevel_0()
	{
		using namespace GameConst;

		const Vec2Int ChunkZero(GAME_AREA_OFFSET_W, GAME_AREA_OFFSET_H);
		const Vec2Int ChunkOffset(GAME_CHUNK_W, GAME_CHUNK_H);
		const Vec2Int ChunkOffset_X(GAME_CHUNK_W, 0);
		const Vec2Int ChunkOffset_Y(0, GAME_CHUNK_H);

		const Vec2Int ChunkLastOffset_X(GAME_AREA_H1, 0);
		const Vec2Int ChunkLastOffset_Y(0, GAME_AREA_W1);

		const Vec2Int BasePosition(GAME_AREA_MID_W, GAME_AREA_H1);

		const Vec2Int PlayerStart = BasePosition - ChunkOffset_X * 2;

		// Level walls:
		{
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 0);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 1);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 3);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 4);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 0);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 1);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 3);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 4);
			
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 0);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 1);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 3);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 0);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 1);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 3);
			
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 0);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 1);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 3);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 4);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 0);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 1);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 3);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 4);
			
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 7);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 2);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 3);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkOffset_Y * 8 + ChunkLastOffset_X);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkOffset_Y * 8 - ChunkOffset_X * 2 + ChunkLastOffset_X);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkOffset_Y * 8 - ChunkOffset_X * 3 + ChunkLastOffset_X);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 5);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 7);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 5);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 7);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 5);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 7);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 6);
			
			// around base
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 7);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 6);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 5);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 7);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 5);
			//
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 8);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 9);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 10);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 8);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 9);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 10);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 8);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 9);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 10);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 8);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 9);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 10);
		}

		// Spawn player tank
		PlayerTank = SpawnActorFromClass<Tank>("MyTank", PlayerStart, Anchor::BOTTOM);

	}

	void TankiLevel_0::OnTick(float DeltaTime)
	{
	}

}