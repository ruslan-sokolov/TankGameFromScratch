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
		Vec2Int ActorPositionOffset;

		// if true, then every time when actor pos change, component will update it's pos with ActorPos + CompOffset
		bool bPosAttachedToActor = true;

		/** handle new actor position translation to component */
		inline void OnActorPositionChange(const Vec2Int& NewActorPosition);

	public:
		BaseEntity* GetEntity() const { return Entity; }

		/*
		 * Control comp pos to actor pos attachment, 
		 * if true - then on actor pos update, comp will change pos with it's offset  
		 */
		inline void SetFlagPosAttachedToActor(bool bPosIsAttached) { bPosAttachedToActor = bPosIsAttached; }

		/** Set new component position with offset value from actor position*/
		inline void SetRelativePosition(const Vec2Int& PosOffsetFromActor);
		/** Change component absolute position */
		inline void SetAbsolutePosition(const Vec2Int& NewWorldPosition);

		inline Vec2Int GetRelativePosition() const { return ActorPositionOffset; }
		inline Vec2Int GetAbsolutePosition() const { return Entity ? Entity->GetPosition() : 0; }

		/** todo: This should be changed to set scale instead */
		inline void SetSize(const Vec2Int& NewSize) { if (Entity) Entity->SetSize(NewSize); }
		inline Vec2Int GetSize() const { return Entity ? Entity->GetSize() : 0; }

		BaseEntityComponent(Actor* ActorOwner) :
			ActorComponent(ActorOwner, ActorComponentType::EntityComponent) {}

		~BaseEntityComponent() { delete Entity; }
	};

	/*
	 * EntityComponent template, for entities like SpriteEntity, SpriteFlipFlop, SpriteSequence
	 * Template class should be derrived from BaseEntity
	 */
	template <class T> class EntityComponent : public BaseEntityComponent
	{
	public:
		template <typename... Args>
		EntityComponent(Args ... args) = delete;

		T* GetSprite() { return static_cast<T*>(Entity); }
	};
	
	// Sprite comp
	template <> template <>
	inline EntityComponent<SpriteEntity>::EntityComponent(Actor* ActorOwner, std::string Name, Vec2Int Position,
		const char* TexturePath)
		: BaseEntityComponent(ActorOwner)
	{
		InitEntity(new SpriteEntity(Name, TexturePath, Position));
	}

	// SpriteFlipFlop comp
	template <> template <>
	inline EntityComponent<SpriteFlipFlop>::EntityComponent(Actor* ActorOwner, std::string Name, Vec2Int Position,
		float FlipFlopRate, const char* TextureFlipPath, const char* TextureFlopPath)
		: BaseEntityComponent(ActorOwner)
	{
		InitEntity(new SpriteFlipFlop(Name, TextureFlipPath, TextureFlopPath, Position, FlipFlopRate));
	}
	
	// SpriteSequence comp
	template<> template <>
	inline EntityComponent<SpriteSequence>::EntityComponent(Actor* ActorOwner, std::string Name, Vec2Int Position, 
		float AnimRate, std::initializer_list<const char*> TexturePathList)
		: BaseEntityComponent(ActorOwner)
	{
		InitEntity(new SpriteSequence(Name, TexturePathList, Position, AnimRate));
	}
}
