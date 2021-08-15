#include "PickupBaseActor.h"

#include <Game/Game.h>
#include <Framework2D/Systems/SystemTimer.h>

namespace Game {

	PickupBase::PickupBase(const std::string& Name, const Vec2& Position, const std::string& IconTexPath)
		: Actor(Name, Position)
	{
		// Enable collision
		EnableCollision(CollisionType::CT_Static);

		// Create actor components
		Icon_SpriteComp = new EntityComponent<SpriteEntity>((Actor*)this, Name, Position, IconTexPath.c_str());
		
		// Initialize actor size
		SetSize(Icon_SpriteComp->GetSize());

		// Pickable default lifespan
		SetActorLifeTime(GameConst::PICKUP_PICK_TIME);

		// Set flick fx timer
		SystemTimer::SetTimer(TimerHandle_Flick, TIMER_CALLBACK(PickupBase::FlickFX), GameConst::PICKUP_FLICK_RATE, true,
			GameConst::PICKUP_TIME_START_FLICK);
	}

	void PickupBase::FlickFX()
	{
		bFlickShow = !bFlickShow;
		Icon_SpriteComp->GetEntity()->SetEnableRender(bFlickShow);
	}

	inline void PickupBase::Pick(Actor* Picker)
	{
		if (OnPick(Picker))
		{
			Destroy();
		}
	}

	void PickupBase::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{
		if (auto A = dynamic_cast<Actor*>(Other))
		{
			Pick(A);
		}
	}

	void PickupBase::OnDestroy()
	{
		SystemTimer::RemoveTimer(TimerHandle_Flick);
	}
}
