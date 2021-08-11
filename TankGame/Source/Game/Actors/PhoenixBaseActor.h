#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>
#include <Framework2D/Gameplay/Actor/Components/HealthComponent.h>

namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent 
	 * 
	 */
	class PhoenixBase : public Framework2D::Actor
	{
	protected:
		class HealthComponent* HealthComp;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		PhoenixBase(const std::string& Name, const Vec2& Position);

		// HealthComp cb
		void OnDeath();

		static PhoenixBase* SpawnDefaultBase(Level* Level, const Vec2& Position, Anchor Anchor);
	};
}
