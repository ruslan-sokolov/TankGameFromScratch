#pragma once

#include "ActorComponent.h"
#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>
#include <Framework2D/Graphic2D/Entities/SpriteFlipFlop.h>
#include <Framework2D/Graphic2D/Entities/SpriteSequence.h>

namespace Framework2D {

	/*
	 * Entity Actor Component, component which resposible for visual representation of actor
	 */
	template <class T>
	class FRAMEWORK2D_API EntityComponent : public ActorComponent, public T
	{
	protected:
		~EntityComponent() {};

	public:
		template <typename... Args>
		inline EntityComponent(Args&& ... args) = delete;
	};

	template <> template <>
	inline EntityComponent<SpriteEntity>::EntityComponent(Actor*&& ActorOwner, const std::string&& Name,
		const std::string&& TexturePath, const VecInt2D&& Position)
		: ActorComponent(ActorOwner, ActorComponentType::EntityComponent),
		SpriteEntity(Name, TexturePath, Position) {}

	template <> template <>
	inline EntityComponent<SpriteFlipFlop>::EntityComponent(Actor*&& ActorOwner, const std::string&& Name,
		const std::string&& TextureFlipPath, const std::string&& TextureFlopPath,
		const VecInt2D&& Position, const float&& FlipFlopRate)
		: ActorComponent(ActorOwner, ActorComponentType::EntityComponent),
		SpriteFlipFlop(Name, TextureFlipPath, TextureFlopPath, Position, FlipFlopRate) {}

	template<> template <>
	inline EntityComponent<SpriteSequence>::EntityComponent(Actor*&& ActorOwner, const std::string&& Name,
		const std::initializer_list<const char*>&& TexturePathList, const VecInt2D&& Position, const float&& AnimRate)
		: ActorComponent(ActorOwner, ActorComponentType::EntityComponent),
		SpriteSequence(Name, TexturePathList, Position, AnimRate) {}
}
