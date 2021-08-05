#include "BlockSolidActor.h"

namespace Game {

	BlockSolid::BlockSolid(const std::string& Name, const Vec2& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		EnableCollision();

		// Create actor components
		BrickSpriteComp = new EntityComponent<SpriteEntity>((Actor*)this, "Sprite_" + Name, Position, ResPath::T_BRICK_BASE);
		
		HealthComp = new Framework2D::HealthComponent(this);
		HealthComp->SetHealth(GameConst::BRICK_BASIC_HEALTH, true);
		HealthComp->SetOnDeathCb(HEALTH_ON_DEATH_CB(BlockSolid::Destroy));

		// Initialize actor size
		SetSize(BrickSpriteComp->GetSize());
	}
}