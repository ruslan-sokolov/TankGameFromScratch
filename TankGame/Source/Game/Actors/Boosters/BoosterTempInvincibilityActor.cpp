#include "BoosterTempInvincibilityActor.h"

#include <Framework2D/Gameplay/Level.h>
#include <Game/Game.h>

namespace Game {

	BoosterTempInvincibility::BoosterTempInvincibility(const std::string& Name, const Vec2& Position)
		: BoosterBase(Name, Position, GameConst::BOOSTER_RESPAWN_PROTECTION_TIME)
	{
	}

	void BoosterTempInvincibility::OnActivated(Actor* Activator)
	{
		if (ActivatorHealthComp = Activator->GetComponentByClass<HealthComponent>())
		{
			GAME_LOG(info, "BoosterTempInvincibility for {} activated", ActivatorHealthComp->GetActor()->GetName());
			ActivatorHealthComp->SetCanBeDamaged(false);
		}
			
	}

	void BoosterTempInvincibility::OnExpired()
	{
		if (ActivatorHealthComp)
		{
			GAME_LOG(info, "BoosterTempInvincibility for {} expired", ActivatorHealthComp->GetActor()->GetName());
			ActivatorHealthComp->SetCanBeDamaged(true);
		}
	}

	BoosterTempInvincibility* BoosterTempInvincibility::SpawnBoosterTempInvincibility(Level* InLevel, const std::string& Name)
	{
		ENGINE_ASSERT(InLevel, "BoosterTempInvnincibility::SpawnBoosterTempInvincibility(Level*) Level is nullptr!!");

		if (InLevel)
		{
			auto BoosterInvincibility = InLevel->SpawnActorFromClass<BoosterTempInvincibility>(Name, (Vec2)0, (Anchor)0);
			return BoosterInvincibility;
		}
		return nullptr;
	}

}