#include "TankActor.h"

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	Tank::Tank(const std::string& Name, const VecInt2D& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		SetEnableCollision(true);

		// Create actor components
		TankUpComp = new EntityComponent<SpriteEntity>((Actor*)this, Name, Position, ResPath::T_TANK_UP_0);

		auto TankLeft = new EntityComponent<SpriteFlipFlop>((Actor*)this, Name, Position, 0.3f, ResPath::T_TANK_LEFT_0, ResPath::T_TANK_LEFT_1);
		TankLeft->SetRelativePosition({ 50, 0 });

		auto BoomComp = new EntityComponent<SpriteSequence>((Actor*)this, Name, Position, 0.2f,
			std::initializer_list<const char*>{ ResPath::T_BOOM_BIG_0, ResPath::T_BOOM_BIG_1, ResPath::T_BOOM_SMALL_0, ResPath::T_BOOM_SMALL_1, ResPath::T_BOOM_SMALL_2 } );
		BoomComp->SetRelativePosition({ 0, -100 });

		// Initialize actor size
		SetSize(TankUpComp->GetSize());
	}

	void Tank::OnTick(float DeltaTime)
	{

	}

	void Tank::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{

	}

}