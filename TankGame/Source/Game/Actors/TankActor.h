#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	using namespace Framework2D;

	/*
	 * This class is represent main AI/Player controlled actor - tank
	 *
	 */
	class Tank : public Framework2D::Actor
	{
	protected:
		class EntityComponent<SpriteEntity>* TankUpComp;


	public:
		/*
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */
		Tank(const std::string& Name, const VecInt2D& Position);
		
		// frame per frame logic, no need to call Framework2D::Actor implementation
		virtual void OnTick(float DeltaTime) override;

		virtual void OnCollide(BaseEntity* Other, CollisionFilter Filter) override;


	};
}
