#include "BulletActor.h"

#include <Framework2D/Gameplay/Level.h>
#include <Game/Actors/TankActor.h>

namespace Game {

	Bullet::Bullet(const std::string& Name, const Vec2& Position, Direction SpawnDirection)
		: Actor(Name, Position)
	{
		// Enable collision
		EnableCollision(true);

		// Actor defaults
		Damage = 1.f;
		Speed = 300.f;

		const char* BulletTexPath;
		switch (SpawnDirection)
		{
		case Direction::LEFT:
			BulletTexPath = ResPath::T_BULLET_LEFT;
			break;
		case Direction::RIGHT:
			BulletTexPath = ResPath::T_BULLET_RIGHT;
			break;
		case Direction::DOWN:
			BulletTexPath = ResPath::T_BULLET_DOWN;
			break;
		default:
			BulletTexPath = ResPath::T_BULLET_UP;
		}

		BulletDirection = SpawnDirection;
		DirectionVec = DirectionToVec2(SpawnDirection);

		// Create actor components
		BulletSpriteComp = new EntityComponent<SpriteEntity>((Actor*)this, Name, Position, BulletTexPath);

		// Initialize actor size
		SetSize(BulletSpriteComp->GetSize());
	}

	void Bullet::OnTick(float DeltaTime)
	{
		Vec2 NewPosition = GetPosition() + DirectionVec * (Speed * DeltaTime);
		SetPosition(NewPosition, true);
	}

	void Bullet::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{
		if (Other == Instigator) return; // tank can't shoot itself

		if (Instigator)
			Instigator->ActiveBullet = nullptr;
		
		Destroy();
	}

	void Bullet::SetInstigator(Tank* Instigator)
	{
		this->Instigator = Instigator;
		Instigator->AddToCollisionFilter(this);
	}
}