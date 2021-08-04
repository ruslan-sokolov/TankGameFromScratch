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
		bool bCompTickEnable = false;
		virtual void OnCompTick(float DeltaTime) {};

	public:
		virtual ~ActorComponent() {}

		void SeCompTickEnable(bool bCanTick) { this->bCompTickEnable = bCompTickEnable; }
		bool IsCompTickEnabled() const { return bCompTickEnable; }
		
		ActorComponentType GetType() const { return Type; }
		Actor* GetActor() const { return Owner; }
	
	protected:
		ActorComponentType Type;
		Actor* Owner;

		// can be called only in derrived
		inline ActorComponent(Actor* Owner, ActorComponentType Type);
	};

}
