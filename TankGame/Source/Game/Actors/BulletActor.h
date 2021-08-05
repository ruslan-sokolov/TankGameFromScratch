#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	using namespace Framework2D;

	class Tank;

	/*
	 * This class is represent bullet shooted from tank actor
	 * 
	 */
	class Bullet : public Framework2D::Actor
	{
	protected:
		EntityComponent<SpriteEntity>* BulletSpriteComp;
		
		Direction BulletDirection;
		Vec2 DirectionVec;

		float Damage;
		float Speed;

		Tank* Instigator;

	public:
		/* 
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */ 
		Bullet(const std::string& Name, const Vec2& Position, 
			Tank* Instigator, Direction SpawnDirection, float Speed, float Damage);

		// frame per frame logic, no need to call Framework2D::Actor implementation
		virtual void OnTick(float DeltaTime) override;

		// will be called when actor overlaps with other entity with enabled collision
		virtual void OnCollide(BaseEntity* Other, CollisionFilter Filter) override;

		static Bullet* SpawnBasicBullet(Tank* Instigator);
	};
}
