#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>
#include <Framework2D/Gameplay/Actor/Components/HealthComponent.h>

namespace Game {

	using namespace Framework2D;

	class BlockModular;

	/*
	 * This class is represent fragment of modular block, 
	 * which is block constructed from smaller blocks in 4x4 matrix
	 * 
	 */
	class BlockFragment : public Framework2D::Actor
	{
		friend class BlockModular;

	protected:
		HealthComponent* HealthComp;
		EntityComponent<SpriteEntity>* SpriteComp;

		BlockModular* ModularOwner = nullptr;
		int ModularIndex = -1;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		BlockFragment(const std::string& Name, const Vec2& Position, const std::string& TexPath, float Health);

		virtual void OnDestroy() override;

		BlockModular* GetOwner() const { return ModularOwner; }
		int GetOwnerIndex() const { return ModularIndex; }

		// health comp callbacks
		void OnDamage(float Damage, Direction From, Actor* Instigator);
		void OnDeath();
	};
}
