#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent bullet collision fx
	 * 
	 */
	class Boom : public Framework2D::Actor
	{
	protected:


	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		Boom(const std::string& Name, const Vec2& Position, std::initializer_list<const char*> BoomTexPathList, float AnimRate);

		static Boom* SpawnBoomSmall(Level* Level, const Vec2& Position);
		static Boom* SpawnBoomBig(Level* Level, const Vec2& Position);
	};
}
