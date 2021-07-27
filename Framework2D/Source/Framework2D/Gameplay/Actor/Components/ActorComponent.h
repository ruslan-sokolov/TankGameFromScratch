#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {
	
	class Actor;

	enum class ActorComponentType
	{
		LogicComponent = 0,
		EntityComponent = 1
	};

	/*
	 * This Class is interface for Actor components
	 */
	class FRAMEWORK2D_API ActorComponent
	{
		friend class Actor;

	protected:
		ActorComponentType Type;
		Actor* Owner;

		ActorComponent(Actor* Owner, ActorComponentType Type) : Owner(Owner), Type(Type) {}
		virtual ~ActorComponent() {}

		ActorComponentType GetType() const { return Type; }
		Actor* GetActor() const { return Owner; }
	};

}
