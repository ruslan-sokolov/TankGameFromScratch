#include <PCH_Framework.h>
#include "Collision.h"

#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

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

}