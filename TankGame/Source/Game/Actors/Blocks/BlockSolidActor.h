#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>
#include <Framework2D/Gameplay/Actor/Components/HealthComponent.h>

namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent 
	 * 
	 */
	class BlockSolid : public Framework2D::Actor
	{
	protected:
		EntityComponent<SpriteEntity>* BrickSpriteComp;
		HealthComponent* HealthComp;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		BlockSolid(const std::string& Name, const Vec2& Position);
	};
}
