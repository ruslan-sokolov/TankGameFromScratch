#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Framework2D/Structs/Vectors.h>

namespace Framework2D {

	struct Vec2;

	// simplest collision filter, used in setPosition()
	enum class CollisionFilter
	{
		CF_IGNORE,  // no collision check, set newPosition
		CF_OVERLAP, // set newPosition, calls onCollide(this Filter=Overlap) for overlapped instance
		CF_BLOCK,  // don't set newPosition, calls onCollide(this, Filter=Block) if collided with other instance (can collide with wall).
	};

	enum class CollisionType
	{
		CT_Static = 0,
		CT_Dynamic = 1,
		CT_Projectile = 2,  // very fast dynamic
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

	inline bool CheckBoxCollision(const Vec2& LeftPos, const Vec2& LeftSize, const Vec2& RightPos, const Vec2 RightSize)
	{
		if (LeftPos.X < RightPos.X + RightSize.X && LeftPos.X + LeftSize.X > RightPos.X &&
			LeftPos.Y < RightPos.Y + RightSize.Y && LeftPos.Y + LeftSize.Y > RightPos.Y)
			return true;
		return false;
	}

}