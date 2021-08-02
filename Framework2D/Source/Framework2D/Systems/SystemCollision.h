#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <vector>
#include <algorithm>

namespace Framework2D
{
	class BaseEntity;

	/*
	 * This static class handles collision for instances inherited from EntityBase
	 * in main method CheckCollisionsAllOverlap() there loop which check if unique pair of Objects Collides and call onCollide() for each;
	 * Can check collision for separate instances in CheckCollision(Filter);
	 */
	class FRAMEWORK2D_API SystemCollision
	{
		// different collidables containers to reduce complexity from around 0.5*n^2 to 0.5 * m * (m - 1) + m * n, but m is small
		static inline std::vector<BaseEntity*> StaticCollidables;
		static inline std::vector<BaseEntity*> DynamicCollidables;

	public:

		/** include intity to collision detection conteiner */
		static inline void AddEntity(BaseEntity* Entity, bool bEntityIsDynamic)
		{
			if (bEntityIsDynamic)
				DynamicCollidables.emplace_back(Entity);
			else
				StaticCollidables.emplace_back(Entity);
		}

		/** remove from collision detection set */
		static inline void RemoveEntity(BaseEntity* Entity, bool bEntityIsDynamic)
		{
			if (bEntityIsDynamic)
			{
				auto It = std::find(DynamicCollidables.begin(), DynamicCollidables.end(), Entity);
				if (It != DynamicCollidables.end())
					DynamicCollidables.erase(It);
			}
			else
			{
				auto It = std::find(StaticCollidables.begin(), StaticCollidables.end(), Entity);
				if (It != StaticCollidables.end())
					StaticCollidables.erase(It);
			}

		}

		/** clear collision detection set, can be used on level change */
		static void ClearCheckCollisionSet();

		/** handle OnCollide() for each unique pair of collidable entities. */
		static void CheckCollisionAll();

	};
}
