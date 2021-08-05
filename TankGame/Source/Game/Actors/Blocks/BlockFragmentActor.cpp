#include "BlockFragmentActor.h"

#include <Framework2D/Gameplay/Level.h>

#include "BlockModularActor.h"

namespace Game {

	BlockFragment::BlockFragment(const std::string& Name, const Vec2& Position,
		const std::string& TexPath, float Health)
		: Actor(Name, Position)
	{
		// Enable static collision
		EnableCollision(false);

		// Create actor components
		SpriteComp = new EntityComponent<SpriteEntity>((Actor*)this, Name, Position, TexPath.c_str());
		
		HealthComp = new HealthComponent((Actor*)this);
		HealthComp->SetHealth(Health, true);
		HealthComp->SetOnDamageCb(HEALTH_ON_DAMAGE_CB(BlockFragment::OnDamage));
		HealthComp->SetOnDeathCb(HEALTH_ON_DEATH_CB(BlockFragment::OnDeath));

		// Initialize actor size
		SetSize(SpriteComp->GetSize());
	}

	void BlockFragment::OnDestroy()
	{
		if (ModularOwner)
		{
			ModularOwner->FragmentBlockDestroyed(ModularIndex);
		}
	}

	void BlockFragment::OnDamage(float Damage, Direction From, Actor* Instigator)
	{
		if (ModularOwner)
		{
			ModularOwner->FragmentBlockDamaged(ModularIndex, Damage, From, Instigator);
		}
	}

	void BlockFragment::OnDeath()
	{
		Destroy();
	}

}