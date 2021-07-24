#include "PCH_Framework.h"
#include "SystemCollision.h"

#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

	// Static
	std::set<BaseEntity*> SystemCollision::CollidableSet;

	// for now this function only generetes CF_BLOCK when collided
	// and also save and call onCollide only for single closest collided Entity
	// todo: handle collision filter properly
	void SystemCollision::CheckCollisionAll()
	{
		if (!CollidableSet.size()) return;

		std::set<BaseEntity*>::iterator IterLeft;
		std::set<BaseEntity*>::iterator IterRight;

		BaseEntity* CollidableLeft;
		BaseEntity* CollidableRight;

		// Clear prev collision results
		for (IterLeft = CollidableSet.begin(); IterLeft != CollidableSet.end(); ++IterLeft)
		{
			(*IterLeft)->LastCollisonResult = CollisionCheckResult();
		}

		// Traverse unique paors loop and get result // time complexity: O( 0.5 * n * (n - 1))
		for (IterLeft = CollidableSet.begin(); std::next(IterLeft) != CollidableSet.end(); IterLeft++)
		{
			CollidableLeft = *(IterLeft);

			IterRight = IterLeft; 
			++IterRight;

			for (IterRight; IterRight != CollidableSet.end(); ++IterRight) 
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

		// Handle onCollide() and Position Sweep
		for (IterLeft = CollidableSet.begin(); IterLeft != CollidableSet.end(); ++IterLeft)
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
		CollidableSet.clear();
	}

}


