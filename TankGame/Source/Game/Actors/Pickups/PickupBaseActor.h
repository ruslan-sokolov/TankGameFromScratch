#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent base of pickup for boosters etc, all pickups should inherit from this interface
	 * Visually it represented only by basic sprite
	 * Right now this has simple logic -> onCollide calls Pick() then call virtual OnPick(), if onPick() success -> destroy pickup
	 * 
	 * We use global values GameConst::PICKUP_PICK_TIME, GameConst::PICKUP_TIME_START_FLICK, GameConst::PICKUP_FLICK_RATE
	 * to set timer on which booster can be picked, and also visualizing this by flick fx
	 */
	class PickupBase : public Framework2D::Actor
	{
		/** if true - Icon will be showed, if false - Icon will be hided */
		bool bFlickShow = true;
		TimerHandle TimerHandle_Flick;
		void FlickFX();

	protected:
		EntityComponent<SpriteEntity>* Icon_SpriteComp;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		PickupBase(const std::string& Name, const Vec2& Position, const std::string& IconTexPath);

		// will be called when actor overlaps with other entity with enabled collision
		virtual void OnCollide(BaseEntity* Other, CollisionFilter Filter) override final;

		virtual void OnDestroy() override;

		inline void Pick(Actor* Picker);

		// should return true if success else false, on true will be destroyed
		virtual bool OnPick(Actor* Picker) = 0;

	};
}
