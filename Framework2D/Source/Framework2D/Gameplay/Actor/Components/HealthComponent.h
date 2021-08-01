#pragma once

#include "ActorComponent.h"

#include <functional>
#include <Framework2D/Structs/Direction.h>

namespace Framework2D
{

	/*
	 * Health Actor Component, can be used in Actors that can be damaged
	 */
	class FRAMEWORK2D_API HealthComponent : public ActorComponent
	{
		using OnDeathCbFn = std::function<void()>;
		using OnDamageCbFn = std::function<void(int Damage, Direction From, Actor* Instigator)>;

		int Health = 1;
		int BaseHealth = 1;
		bool bIsDead = false;		

		OnDamageCbFn OnDamageCb;
		OnDeathCbFn OnDeathCb;

	protected:
		~HealthComponent() {}

	public:
		HealthComponent(Actor* ActorOwner)
			: ActorComponent(ActorOwner, ActorComponentType::LogicComponent) {}

		/** Get Current Health */
		inline int GetHealth() const { return Health; }
		/** Get Base Full Health */
		inline int GetBaseHealth() const { return BaseHealth; }
		/** True if Health is was zero and not reseted back */
		inline bool IsDead() const { return bIsDead; }

		inline void SetOnDamageCb(OnDamageCbFn&& OnDamageCb) { this->OnDamageCb = OnDamageCb; }
		inline void SetOnDeathCb(OnDeathCbFn&& OnDeathCb) { this->OnDeathCb = OnDeathCb; }

		/** Will be called when health reached zero */
		inline void OnDeath() { OnDeathCb(); }

		/** Set Health, flag bResetBase allow to reset base full HP */
		inline void SetHealth(int NewHealth, bool bResetBaseHealth = false)
		{
			if (NewHealth <= 0)
			{
				Health = 0;
				bIsDead = true;
				OnDeath();
			}
			else
			{
				Health = NewHealth;
				if (bResetBaseHealth)
				{
					BaseHealth = NewHealth;
					bIsDead = false;
				}
			}
		}

		/** Can be called from elsewhere to damage another actor */
		inline void OnDamage(int Damage, Direction From, Actor* Instigator)
		{
			SetHealth(Health - Damage);
			OnDamageCb(Damage, From, Instigator);
		}

#define HEALTH_COMP_CB(x) std::bind(&x, this);
	};

}
