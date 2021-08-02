#include "PCH_Framework.h"
#include "SystemCollision.h"

#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

	// for now this function only generetes CF_BLOCK when collided
	// and also save and call onCollide only for single closest collided Entity
	// todo: handle collision filter properly
	void SystemCollision::CheckCollisionAll()
	{
		if (!DynamicCollidables.size()) return;  // if nothing register as movable do nothing

		std::vector<BaseEntity*>::iterator IterLeft;
		std::vector<BaseEntity*>::iterator IterRight;

		BaseEntity* CollidableLeft;
		BaseEntity* CollidableRight;

		// Clear prev collision results for static
		for (IterLeft = StaticCollidables.begin(); IterLeft != StaticCollidables.end(); ++IterLeft)
			(*IterLeft)->LastCollisonResult = CollisionCheckResult();

		// Check all dynamic against all static, complexity: m * n
		for (IterLeft = DynamicCollidables.begin(); IterLeft != DynamicCollidables.end(); IterLeft++)
		{
			CollidableLeft = *(IterLeft);
			CollidableLeft->LastCollisonResult = CollisionCheckResult();  // clear prev collision result for dynamic

			for (IterRight = StaticCollidables.begin(); IterRight != StaticCollidables.end(); ++IterRight)
			{
				CollidableRight = *(IterRight);

				if (CollidableLeft->CanCollideWith(CollidableRight, true))  // process black/white list filter
				{
					if (CollidableLeft->IsCollidingWith(CollidableLeft->GetPosition(true), CollidableRight, CollidableRight->GetPosition(true)))
					{
						CollidableLeft->LastCollisonResult.UpdateResult(CollidableLeft, CollidableRight);
						CollidableRight->LastCollisonResult.UpdateResult(CollidableRight, CollidableLeft);
					}
				}
			}
		}

		// Check dynamic against dynamic (loop with unique pairs traversing
	    // complexity: 0.5 * m * (m - 1), total complexity: 0.5 * m * (m - 1) + m * n, but consider that m is small
		for (IterLeft = DynamicCollidables.begin(); std::next(IterLeft) != DynamicCollidables.end(); IterLeft++)
		{
			CollidableLeft = *(IterLeft);

			IterRight = IterLeft;
			++IterRight;

			for (IterRight; IterRight != DynamicCollidables.end(); ++IterRight)
			{
				CollidableRight = *(IterRight);

				if (CollidableLeft->CanCollideWith(CollidableRight, true))  // process black/white list filter
				{
					if (CollidableLeft->IsCollidingWith(CollidableLeft->GetPosition(true), CollidableRight, CollidableRight->GetPosition(true)))
					{
						CollidableLeft->LastCollisonResult.UpdateResult(CollidableLeft, CollidableRight);
						CollidableRight->LastCollisonResult.UpdateResult(CollidableRight, CollidableLeft);
					}
				}
			}
		}

		// Handle onCollide() for Static collidables
		for (IterLeft = StaticCollidables.begin(); IterLeft != StaticCollidables.end(); ++IterLeft)
		{
			CollidableLeft = *(IterLeft);

			CollisionCheckResult& Result = CollidableLeft->LastCollisonResult;

			if (Result.bCollided)
				CollidableLeft->OnCollide(Result.LastCollided, CollisionFilter::CF_BLOCK);
		}

		// Handle onCollide() and Position Sweep for Dynamic collidables
		for (IterLeft = DynamicCollidables.begin(); IterLeft != DynamicCollidables.end(); ++IterLeft)
		{
			CollidableLeft = *(IterLeft);

			CollisionCheckResult& Result = CollidableLeft->LastCollisonResult;

			if (Result.bCollided)
				CollidableLeft->OnCollide(Result.LastCollided, CollisionFilter::CF_BLOCK);

			if (CollidableLeft->bNextPositionRelevent)
				CollidableLeft->HandleSweepPosition(CollidableLeft->NextPosition, CollidableLeft->LastCollisonResult);
		}
	}

	void SystemCollision::ClearCheckCollisionSet()
	{
		StaticCollidables.clear();
		DynamicCollidables.clear();
	}

}
