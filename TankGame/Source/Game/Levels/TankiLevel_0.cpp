#include "TankiLevel_0.h"

#include <Game/Actors/BrickSolidActor.h>

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
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 0, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 1, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 3, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 4, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 0, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 1, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 3, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 4, Anchor::TOP_LEFT);
			
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 0, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 1, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 4 + ChunkOffset_Y * 3, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 0, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 1, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 6 + ChunkOffset_Y * 3, Anchor::TOP_LEFT);
			
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 0, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 1, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 3, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 4, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 0, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 1, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 3, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 4, Anchor::TOP_LEFT);
			
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 7, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 2, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 7 + ChunkOffset_X * 3, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkOffset_Y * 8 + ChunkLastOffset_X, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkOffset_Y * 8 - ChunkOffset_X * 2 + ChunkLastOffset_X, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkOffset_Y * 8 - ChunkOffset_X * 3 + ChunkLastOffset_X, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 5, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 6 + ChunkOffset_X * 7, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 5, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 7, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 5, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 9 + ChunkOffset_X * 7, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 8 + ChunkOffset_X * 6, Anchor::TOP_LEFT);
			
			// around base
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 7, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 6, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 11 + ChunkOffset_X * 5, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 7, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset_Y * 12 + ChunkOffset_X * 5, Anchor::TOP_LEFT);
			//
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 8, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 9, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 0 + ChunkOffset_Y * 10, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 8, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 9, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 2 + ChunkOffset_Y * 10, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 8, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 9, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 8 + ChunkOffset_Y * 10, Anchor::TOP_LEFT);
			
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 8, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 9, Anchor::TOP_LEFT);
			SpawnActorFromClass<BrickSolid>("Brick", ChunkZero + ChunkOffset + ChunkOffset_X * 10 + ChunkOffset_Y * 10, Anchor::TOP_LEFT);
		}

		// Spawn player tank
		PlayerTank = Tank::SpawnBasicPlayerTank(this, PlayerSpawnPoint);
	}

	void TankiLevel_0::OnTick(float DeltaTime)
	{
	}

}