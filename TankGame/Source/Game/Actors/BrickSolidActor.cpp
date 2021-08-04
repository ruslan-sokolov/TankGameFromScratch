#include "BrickSolidActor.h"

namespace Game {

	BrickSolid::BrickSolid(const std::string& Name, const Vec2& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		EnableCollision();

		// Create actor components
		BrickSpriteComp = new EntityComponent<SpriteEntity>((Actor*)this, "Sprite_" + Name, Position, ResPath::T_BRICK_BASE);
		
		HealthComp = new Framework2D::HealthComponent(this);
		HealthComp->SetHealth(GameConst::BRICK_BASIC_HEALTH, true);
		HealthComp->SetOnDeathCb(HEALTH_COMP_CB(BrickSolid::Destroy));

		// Initialize actor size
		SetSize(BrickSpriteComp->GetSize());
	}

	void BrickSolid::OnTick(float DeltaTime)
	{

	}

	void BrickSolid::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{
		if (Filter == CollisionFilter::CF_BLOCK)
		{
		}
	}
}