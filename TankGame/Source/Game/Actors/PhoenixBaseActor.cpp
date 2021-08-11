#include "PhoenixBaseActor.h"


#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>
#include <Framework2D/Gameplay/Level.h>

#include <Game/Game.h>
#include <Game/Gameplay/TankiGameMode.h>

namespace Game {

	PhoenixBase::PhoenixBase(const std::string& Name, const Vec2& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		EnableCollision(CollisionType::CT_Static);

		// Create actor components
		auto* Sprite = new EntityComponent<SpriteEntity>((Actor*)this, Name, Position, ResPath::T_PHOENIX_PNG);
		
		HealthComp = new HealthComponent(this);
		HealthComp->SetHealth(GameConst::PHOENIX_BASE_HEALTH);
		HealthComp->SetOnDeathCb(HEALTH_ON_DEATH_CB(PhoenixBase::OnDeath));

		// Initialize actor size
		SetSize(Sprite->GetSize());
	}

	void PhoenixBase::OnDeath()
	{
		if (auto GM = dynamic_cast<TankiGameMode*>(GetGM()))
		{
			GM->OnBaseDestroyed();
		}

		Destroy();
	}

	PhoenixBase* PhoenixBase::SpawnDefaultBase(Level* Level, const Vec2& Position, Anchor Anchor)
	{
		return Level->SpawnActorFromClass<PhoenixBase>("PlayerBase", Position, Anchor);
	}
}