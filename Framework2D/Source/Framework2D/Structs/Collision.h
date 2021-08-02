#pragma once

namespace Framework2D {

	// simplest collision filter, used in setPosition()
	enum class CollisionFilter
	{
		CF_IGNORE,  // no collision check, set newPosition
		CF_OVERLAP, // set newPosition, calls onCollide(this Filter=Overlap) for overlapped instance
		CF_BLOCK,  // don't set newPosition, calls onCollide(this, Filter=Block) if collided with other instance (can collide with wall).
	};

	struct FRAMEWORK2D_API CollisionCheckResult
	{
		bool bCollided = false;
		class BaseEntity* LastCollided = nullptr;
		int Distance = 0;
		static CollisionCheckResult DefaultResultOut;

		/** Updating result, LastCollided will be closest one */
		inline void UpdateResult(class BaseEntity* Left, class BaseEntity* Right);
	};

}