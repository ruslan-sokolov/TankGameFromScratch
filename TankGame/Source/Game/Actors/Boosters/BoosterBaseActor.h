#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent base of all boosters class.
	 * Common usage is in pair with Pickup actors - activate booster on pickup picked
	 * Or it can be spawned elsewhere for example, on player respawn give him boost -> respawn protection
	 */
	class BoosterBase : public Framework2D::Actor
	{
	protected:
		/** Time between powerup ticks, if <= 0.f then will be executed in moment and only once*/
		float BoostInterval;

		/** Total times we apply the power up effect */
		int BoostTickNumToExec;

		TimerHandle TimerHandle_BoostTick;

		/** Total number of ticks applied */
		int TicksProcessed = 0;

		// Timer callback, handle custom boost logic-tick-impulse
		void OnTickBoost();

		bool bIsBoostActive = false;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		BoosterBase(const std::string& Name, const Vec2& Position, float BoostInterval, int BoostTickNumToExec = 1);
		
		virtual void OnDestroy() override;

		// start executing boost logic
		void ActivateBoost(Actor* Activator);

		// execute custom logic on activate
		virtual void OnActivated(Actor* Activator) =0;

		// execute custom boost tick logic
		virtual void OnBoostTicked() {}

		virtual void OnExpired() {}
	};
}
