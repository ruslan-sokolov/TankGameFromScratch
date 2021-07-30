#include <PCH_Framework.h>

#include "ActorComponent.h"

#include "../Actor.h"

namespace Framework2D {

	inline ActorComponent::ActorComponent(Actor* Owner, ActorComponentType Type)
		: Owner(Owner), Type(Type)
	{
		// add to owner components list
		Owner->AddComponent(this);
	}

}