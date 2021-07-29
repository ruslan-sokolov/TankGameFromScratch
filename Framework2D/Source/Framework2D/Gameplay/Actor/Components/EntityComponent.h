#pragma once

#include "ActorComponent.h"
#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>
#include <Framework2D/Graphic2D/Entities/SpriteFlipFlop.h>
#include <Framework2D/Graphic2D/Entities/SpriteSequence.h>

namespace Framework2D {

	/*
	 * Actor component, that create and control BaseEntity instance
	 * responsible for visual representation of actor
	 */
	class FRAMEWORK2D_API BaseEntityComponent : public ActorComponent
	{
		friend class Actor;

	protected:
		BaseEntity* Entity = nullptr;

		/** For Entity initialization in derrived classes */
		inline void InitEntity(SpriteEntity* Entity);

		inline void InitEntity(BaseEntity* Entitiy);

		// Component position offset from it's actor position  
		VecInt2D ActorPositionOffset;

		// if true, then every time when actor pos change, component will update it's pos with ActorPos + CompOffset
		bool bPosAttachedToActor = true;

		/** handle new actor position translation to component */
		inline void OnActorPositionChange(const VecInt2D& NewActorPosition);

	public:
		BaseEntity* GetEntity() const { return Entity; }


		/*
		 * Control comp pos to actor pos attachment, 
		 * if true - then on actor pos update, comp will change pos with it's offset  
		 */
		inline void SetFlagPosAttachedToActor(bool bPosIsAttached) { bPosAttachedToActor = bPosIsAttached; }

		/** Set new component position with offset value from actor position*/
		inline void SetRelativePosition(const VecInt2D& PosOffsetFromActor);

		/** Change component absolute position */
		inline void SetAbsolutePosition(const VecInt2D& NewWorldPosition);

		inline VecInt2D GetRelativePosition() const { return ActorPositionOffset; }

		inline VecInt2D GetAbsolutePosition() const { return Entity->GetPosition(); }

		/** todo: This should be changed to set scale instead */
		inline void SetSize(const VecInt2D& NewSize) { Entity->SetSize(NewSize); }

		BaseEntityComponent(Actor* ActorOwner) :
			ActorComponent(ActorOwner, ActorComponentType::EntityComponent) {}

		~BaseEntityComponent() { delete Entity; }
	};

	/*
	 * EntityComponent template, for entities like SpriteEntity, SpriteFlipFlop, SpriteSequence
	 * Template class should be derrived from BaseEntity
	 */
	template <class T>
	class FRAMEWORK2D_API EntityComponent : public BaseEntityComponent
	{
		template <typename... Args>
		inline EntityComponent(Args&& ... args) = delete;
	};

	template <> template <>
	inline EntityComponent<SpriteEntity>::EntityComponent(Actor*&& ActorOwner, const std::string&& Name,
		const std::string&& TexturePath, const VecInt2D&& Position)
		: BaseEntityComponent(ActorOwner) 
	{
		InitEntity(new SpriteEntity(Name, TexturePath, Position));
	}

	template <> template <>
	inline EntityComponent<SpriteFlipFlop>::EntityComponent(Actor*&& ActorOwner, const std::string&& Name,
		const std::string&& TextureFlipPath, const std::string&& TextureFlopPath,
		const VecInt2D&& Position, const float&& FlipFlopRate)
		: BaseEntityComponent(ActorOwner)
	{
		InitEntity(new SpriteFlipFlop(Name, TextureFlipPath, TextureFlopPath, Position, FlipFlopRate));
	}

	template<> template <>
	inline EntityComponent<SpriteSequence>::EntityComponent(Actor*&& ActorOwner, const std::string&& Name,
		const std::initializer_list<const char*>&& TexturePathList, const VecInt2D&& Position, const float&& AnimRate)
		: BaseEntityComponent(ActorOwner)
	{
		InitEntity(new SpriteSequence(Name, TexturePathList, Position, AnimRate));
	}
}
