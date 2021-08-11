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
		{
			EntityGroup->RemoveEntity(this);
		}
	}
	
	inline bool BaseEntity::IsCollidingWith(BaseEntity* Other, const Vec2& OtherPosition)
	{
		if (Other == nullptr) { return false; }

		// if Other is Very Dynamic and this is not, USE UNO REVERSE!!!
		if (Other->IsCollisionVeryDynamic() && !IsCollisionVeryDynamic())
		{
			return Other->IsCollidingWith(this, GetPosition(true));
		}

		const Vec2 OtherSize = Other->GetSize();
		const Vec2 ThisPos = GetPosition(true);

		if (IsCollisionVeryDynamic())  // this is for collision check for very fast projectile
		{
			const Vec2 PrevPos = PrevPosition.NotEqualZero() ? PrevPosition : Position;

			const Vec2 Direction = NextPosition - PrevPos;
			const Vec2 DirectionNormalized = Direction.GetNormalized();

			const float Dist = (Direction).Size();

			const float Dot = std::roundf(Vec2::Dot(DirectionNormalized, Vec2::VecRight));

			const float Cos_Unsigned = Engine::Abs(Dot);
			const float Sin_Unsigned = Engine::Sqrt(1 - Dot * Dot);

			const float OffsetMax_X = Size.X;
			const float OffsetMax_Y = Size.Y;

			const float DistOffset_X = OffsetMax_X * Sin_Unsigned;
			const float DistOffset_Y = OffsetMax_Y * Cos_Unsigned;

			const float DistOffset = Engine::Sqrt(DistOffset_X * DistOffset_X + DistOffset_Y * DistOffset_Y);

			float TempDist = 0;
			float DistOffsetNormalized;
			Vec2 DistPoint;

			while (TempDist < Dist)
			{
				TempDist += DistOffset;
				DistOffsetNormalized = 1.0f - TempDist / Dist;

				DistPoint = Vec2((1.0f - DistOffsetNormalized) * PrevPos.X + DistOffsetNormalized * NextPosition.X,
					             (1.0f - DistOffsetNormalized) * PrevPos.Y + DistOffsetNormalized * NextPosition.Y);

				if (CheckBoxCollision(DistPoint, Size, OtherPosition, OtherSize))
				{
					// debug
					// GetGame()->DrawDebugBox(DistPoint, GetSize(), Vec4::GreenColor, 1.0f);
					return true;
				}
			}

			// debug
			//if (CheckBoxCollision(NextPosition, Size, OtherPosition, OtherSize))
			//{
			//	GetGame()->DrawDebugBox(NextPosition, GetSize(), Vec4::RedColor, 1.0f);
			//	return true;
			//}
		}

		return CheckBoxCollision(ThisPos, Size, OtherPosition, OtherSize);
	}

	inline bool BaseEntity::CanCollideWith(BaseEntity* Collidable, bool bCheckOtherFilterList)
	{
		// todo: bug here somewhere need to fix

		std::vector<BaseEntity*>::iterator Iter;
		Iter = std::find(CollisionFilterList.begin(), CollisionFilterList.end(), Collidable);

		bool bIsInCollidableFilterList = Iter != CollisionFilterList.end();

		bool bCanCollide;

		if (bCollisionFilterIsWhiteList && bIsInCollidableFilterList)
			bCanCollide = true;
		else if (!bCollisionFilterIsWhiteList && !bIsInCollidableFilterList)
			bCanCollide = true;
		else
			bCanCollide = false;

		if (bCheckOtherFilterList)
			bCanCollide = bCanCollide && Collidable->CanCollideWith(this, false); // if check other, then 1 and 1 -> 1 else -> 0

		return bCanCollide;
	}

	inline bool BaseEntity::IsPosGameBound(const Vec2& NewPosition)
	{
		auto Game = GetGame();
		const Vec2& BoundLeft = Game->GetGameBoundLeft();
		const Vec2& BoundRight = Game->GetGameBoundRight();

		if (NewPosition.X < BoundLeft.X) return false;
		if (NewPosition.X + Size.X > BoundRight.X) return false;
		if (NewPosition.Y < BoundLeft.Y) return false;
		if (NewPosition.Y + Size.Y > BoundRight.Y) return false;

		return true;
	}

	inline void BaseEntity::SetPosBoundClamped(Vec2 NewPosition)
	{
		auto Game = GetGame();
		const Vec2& BoundLeft = Game->GetGameBoundLeft();
		const Vec2& BoundRight = Game->GetGameBoundRight();

		// clamp x
		if (NewPosition.X < BoundLeft.X)
		{
			NewPosition.X = BoundLeft.X;
		}
		else if (NewPosition.X + Size.X > BoundRight.X)
		{
			NewPosition.X = BoundRight.X - Size.X;
		}

		// clamp y
		if (NewPosition.Y < BoundLeft.Y)
		{
			NewPosition.Y = BoundLeft.Y;
		}
		else if (NewPosition.Y + Size.Y > BoundRight.Y)
		{
			NewPosition.Y = BoundRight.Y - Size.Y;
		}

		// set new position
		Position = NewPosition;
	}

	inline void BaseEntity::SetPosBlockClamped(const Vec2& NewPosition, BaseEntity* Blocker)
	{
		Vec2 DeltaPos = NewPosition - Position;
		Vec2 BlockerSize = Blocker->Size;
		Vec2 BlockerPos = Blocker->Position;

		Vec2 FixedPos = NewPosition;

		if (DeltaPos.X > 0)  // NewPosition is on the right side from old Position and on left from blocker
		{
			FixedPos.X = BlockerPos.X - Size.X;  // Set to blocker left side x
		}
		else if (DeltaPos.X < 0)
		{
			FixedPos.X = BlockerPos.X + BlockerSize.X; // Set to blocker right side x
		}
		else if (DeltaPos.Y > 0)  // New Position is lower from old position and higher from blocker
		{
			FixedPos.Y = BlockerPos.Y - Size.Y;  // Set to blocker top y
		}
		else if (DeltaPos.Y < 0)
		{
			FixedPos.Y = BlockerPos.Y + BlockerSize.Y; // set to blocker bottom y
		}
		else
		{
			return;
		}

		// set new position
		Position = FixedPos;
	}

	inline void BaseEntity::HandleSweepPosition(const Vec2& NewPosition, const CollisionCheckResult& CollisionResult)
	{
		if (CollisionResult.bCollided)
		{
			SetPosBlockClamped(NewPosition, CollisionResult.LastCollided);
			return;
		}

		if (!IsPosGameBound(NewPosition))
		{
			SetPosBoundClamped(NewPosition);
			OnCollide(InvisibleWall, CollisionFilter::CF_BLOCK);
			return;
		}

		PrevPosition = Position;
		bPrevPositionRelevent = true;
		Position = NewPosition;
		bNextPositionRelevent = false;
	}

	inline void BaseEntity::EnableCollision(CollisionType Type)
	{
		if (!bCollisionEnabled)
		{
			Collision = Type;
			bCollisionEnabled = true;

			SystemCollision::AddEntity(this, IsCollisionDynamic());
		}
	}

	inline void BaseEntity::DisableCollision()
	{
		if (bCollisionEnabled)
		{
			SystemCollision::RemoveEntity(this, IsCollisionDynamic());
			bCollisionEnabled = false;
		}
	}
}
