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
		DisableCollision();

		if (EntityGroup != nullptr)
			EntityGroup->RemoveEntity(this);
	}
	
	inline void BaseEntity::EnableCollision(bool bIsDynamic)
	{
		if (!bCollisionEnabled)
		{
			SystemCollision::AddEntity(this, bIsDynamic);
			bCollisionEnabled = true;
			bIsDynamicCollision = bIsDynamic;
		}
	}

	inline void BaseEntity::DisableCollision()
	{
		if (bCollisionEnabled)
		{
			SystemCollision::RemoveEntity(this, bIsDynamicCollision);
			bCollisionEnabled = false;
		}
	}
}
