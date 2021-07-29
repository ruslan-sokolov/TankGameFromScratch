#include <PCH_Framework.h>
#include "BaseEntity.h"

#include <Framework2D/Systems/SystemCollision.h>
#include <Framework2D/Graphic2D/Groups/Group.h>

namespace Framework2D {

	// static
	CollisionCheckResult CollisionCheckResult::DefaultResultOut;

	class InvisibleWallEntity : public BaseEntity
	{
	public:
		InvisibleWallEntity() : BaseEntity("InvisibleWall") {}
		void OnUpdate(float DeltaTime) {}
		void OnCollide(BaseEntity* Other, CollisionFilter Filter) {}
	};

	BaseEntity* BaseEntity::InvisibleWall = new InvisibleWallEntity();
	//

	BaseEntity::~BaseEntity()
	{
		if (EntityGroup != nullptr)
			EntityGroup->RemoveEntity(this);
	}
	
	inline void CollisionCheckResult::UpdateResult(BaseEntity* Left, BaseEntity* Right)
	{
		bCollided = true;

		int CollidableDistance = (Left->GetPosition() - Right->GetPosition()).Size();

		if (LastCollided == nullptr || CollidableDistance <= Distance)
		{
			Distance = CollidableDistance;
			LastCollided = Right;
		}
	}

	inline void BaseEntity::SetEnableCollision(bool bEnable)
	{
		if (bEnable)
			SystemCollision::AddEntity(this);
		else
			SystemCollision::RemoveEntity(this);

		bCollisionEnabled = bEnable;
	}
}
