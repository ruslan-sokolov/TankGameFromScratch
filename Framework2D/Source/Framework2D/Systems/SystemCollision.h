#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <set>
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
		static std::set<BaseEntity*> CollidableSet;

	public:

		/** include intity to collision detection conteiner */
		static inline void AddEntity(BaseEntity* Entity)
		{
			CollidableSet.emplace(Entity);
		}

		/** remove from collision detection set */
		static inline void RemoveEntity(BaseEntity* Entity)
		{
			auto It = CollidableSet.find(Entity);
			if (It != CollidableSet.end())
				CollidableSet.erase(It);
		}

		/** clear collision detection set, can be used on level change */
		static void ClearCheckCollisionSet();

		/** handle OnCollide() for each unique pair of collidable entities. */
		static void CheckCollisionAll();

	};
}


