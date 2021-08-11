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
		using OnDamageCbFn = std::function<void(float Damage, Direction From, Actor* Instigator)>;

		float Health = 1.f;
		float BaseHealth = 1.f;
		bool bIsDead = false;		

		OnDamageCbFn OnDamageCb;
		OnDeathCbFn OnDeathCb;

	public:
		HealthComponent(Actor* ActorOwner)
			: ActorComponent(ActorOwner, ActorComponentType::LogicComponent) {}

		~HealthComponent() {}

		/** Get Current Health */
		inline float GetHealth() const { return Health; }
		/** Get Base Full Health */
		inline float GetBaseHealth() const { return BaseHealth; }
		/** True if Health is was zero and not reseted back */
		inline bool IsDead() const { return bIsDead; }

		inline void SetOnDamageCb(OnDamageCbFn&& OnDamageCb) { this->OnDamageCb = OnDamageCb; }
		inline void SetOnDeathCb(OnDeathCbFn&& OnDeathCb) { this->OnDeathCb = OnDeathCb; }

		/** Will be called when health reached zero */
		inline void OnDeath() { if (OnDeathCb) OnDeathCb(); }

		/** Set Health, flag bResetBase allow to reset base full HP */
		inline void SetHealth(float NewHealth, bool bResetBaseHealth = false)
		{
			if (NewHealth <= 0.f)
			{
				Health = 0.f;

				if (!bIsDead)
				{
					OnDeath();
					bIsDead = true;
				}
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
		inline void OnDamage(float Damage, Direction From, Actor* Instigator)
		{
			SetHealth(Health - Damage);
			if (OnDamageCb) OnDamageCb(Damage, From, Instigator);
		}

#define HEALTH_ON_DEATH_CB(x) std::bind(&x, this)
#define HEALTH_ON_DAMAGE_CB(x) std::bind(&x, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
	};

}
