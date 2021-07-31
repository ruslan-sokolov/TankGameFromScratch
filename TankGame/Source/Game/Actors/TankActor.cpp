#include "TankActor.h"

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	Tank::Tank(const std::string& Name, const VecInt2D& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		SetEnableCollision(false);

		// Create actor components
		TankUpComp = new EntityComponent<SpriteEntity>((Actor*)this, Name, Position, ResPath::T_TANK_UP_0);

		// Initialize actor size
		SetSize(TankUpComp->GetSize());
	}

	void Tank::OnTick(float DeltaTime)
	{

	}

	void Tank::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{

	}

	inline void Tank::Move(float DeltaTime)
	{

	}

	void Tank::MoveBegin(Direction DirectionTo)
	{
		GAME_LOG(info, "Tank Move begin. Direction: {}", DirectionToString(DirectionTo));
	}

	void Tank::MoveEnd(Direction DirectionTo)
	{
		GAME_LOG(info, "Tank Move end. Direction: {}", DirectionToString(DirectionTo));
	}

	void Tank::Fire()
	{
		GAME_LOG(info, "Tank {} fired!", GetName());
	}

}