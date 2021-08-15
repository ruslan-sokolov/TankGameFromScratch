#pragma once

#include "BoosterBaseActor.h"

#include <Framework2D/Gameplay/Actor/Components/HealthComponent.h>

namespace Game {

	class BoosterTempInvincibility : public BoosterBase
	{
		// need to be set to null if actor deleted!
		HealthComponent* ActivatorHealthComp = nullptr;

	public:
		BoosterTempInvincibility(const std::string& Name, const Vec2& Position);

		virtual void OnActivated(Actor* Activator) override;
		virtual void OnExpired() override;

		static BoosterTempInvincibility* SpawnBoosterTempInvincibility(Level* InLevel, const std::string& Name);
	};

}