#include <PCH_Framework.h>
#include "EntityComponent.h"

#include "../Actor.h"

#include <Framework2D/Layers/Layer2D.h>
#include <Framework2D/Graphic2D/Groups/GroupSprite.h>

namespace Framework2D {

	inline void BaseEntityComponent::InitEntity(SpriteEntity* Sprite)
	{
		this->Entity = Sprite;

		// add to renderer
		// group with name Actor.name not nessesery is GroupSprite type! todo: resolve problem
		Layer2D* MainLayer = GetGame()->GetMainLayer();
		if (Group* group = MainLayer->GetGroup("Actor_" + Owner->GetName()))
		{
			auto groupSprite = static_cast<GroupSprite*>(group);
			groupSprite->AddSprite(Sprite);
		}
		else
		{
			auto groupSprite = new GroupSprite("Actor_" + Owner->GetName());
			groupSprite->AddSprite(Sprite);
			MainLayer->AddGroup(groupSprite);
		}
	}

	inline void BaseEntityComponent::InitEntity(BaseEntity* Entity)
	{
		ENGINE_ASSERT(true, "Not supported yet");
		this->Entity = Entity;
	}

	inline void BaseEntityComponent::OnActorPositionChange(const VecInt2D& NewActorPosition)
	{
		// update current component position with it's offset from actor
		if (bPosAttachedToActor)
			Entity->SetPosition(NewActorPosition + ActorPositionOffset);
			
	}

	inline void BaseEntityComponent::SetRelativePosition(const VecInt2D& PosOffsetFromActor)
	{
		// change current offset and also set new position with offset
		ActorPositionOffset = PosOffsetFromActor;
		ENGINE_LOG(info, "ActorPos {} {} Offset {} {}", Owner->GetPosition().X, Owner->GetPosition().Y, PosOffsetFromActor.X, PosOffsetFromActor.Y);
		Entity->SetPosition(Owner->GetPosition() + PosOffsetFromActor);
	}

	inline void BaseEntityComponent::SetAbsolutePosition(const VecInt2D& NewWorldPosition)
	{
		// regular entity position set
		Entity->SetPosition(NewWorldPosition);
	}
}