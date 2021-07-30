#include "__ActorTempalte.h"


namespace Game {

	__ActorTemplate::__ActorTemplate(const std::string& Name, const VecInt2D& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		SetEnableCollision(false);

		// Create actor components
		auto* TankUp = new EntityComponent<SpriteEntity>((Actor*)this, Name, ResPath::T_TANK_UP_0, Position);

		// Initialize actor size
		SetSize(TankUp->GetSize());
	}

	void __ActorTemplate::OnTick(float DeltaTime)
	{

	}

	void __ActorTemplate::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{

	}

}