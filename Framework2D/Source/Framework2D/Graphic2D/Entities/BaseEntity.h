#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Framework2D/Structs/Vectors.h>
#include <Framework2D/Structs/Direction.h>

#include <Framework2D/Gameplay/Game2D.h>

namespace Framework2D {

	class Group;
	class SystemCollision;

	// using for spawn position adjusting
	enum class Anchor
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	inline Vec2Int GetAnchorOffset(Vec2Int Size, Anchor Anchor)
	{
		Vec2Int Offset{ 0, 0 };

		switch (Anchor)
		{
		case Anchor::CENTER:
			Offset = Size / 2;
			break;
		case Anchor::TOP_RIGHT:
			Offset.X = Size.X;
			break;
		case Anchor::BOTTOM_LEFT:
			Offset.Y = Size.Y;
			break;
		case Anchor::BOTTOM_RIGHT:
			Offset = Size;
			break;
		case Anchor::TOP:
			Offset.X = Size.X / 2;
			break;
		case Anchor::BOTTOM:
			Offset.X = Size.X / 2;
			Offset.Y = Size.Y;
			break;
		case Anchor::LEFT:
			Offset.Y = Size.Y / 2;
			break;
		case Anchor::RIGHT:
			Offset.X = Size.X;
			Offset.Y = Size.Y / 2;
			break;
		default: // Anchor::TOP_LEFT
			break;
		}

		return Offset;
	}

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

	class FRAMEWORK2D_API BaseEntity
	{
		friend class Group;
		friend class SystemCollision;
	
	protected:
		Group* EntityGroup;
		std::string Name;

		BaseEntity(const std::string& Name, const Vec2Int& Size = Vec2Int::VecZero, 
			const Vec2Int& Position = Vec2Int::VecZero, bool bRenderEnable = false) 
			: Name(Name), Size(Size), Position(Position), bRenderEnabled(bRenderEnable), EntityGroup(nullptr) {}

		bool bRenderEnabled;
		bool bCollisionEnabled = false;

		Vec2Int Size;
		Vec2Int Position;

		/** control if Collision Ignore Is BlackList or WhiteList */
		bool bCollisionFilterIsWhiteList = false;
		/** collision filter list, can work as blacklist or as whitelist */
		std::vector<BaseEntity*> CollisionFilterList = {};
		CollisionCheckResult LastCollisonResult;
		Vec2Int NextPosition;
		Vec2Int PrevPosition;
		bool bNextPositionRelevent = false;
		bool bPrevPositionRelevent = false;
		static BaseEntity* InvisibleWall;  // used to informate about collision with game 2d walls bound

	public:
		virtual ~BaseEntity();

		inline Group* GetGroup() const { return EntityGroup; }
		inline bool HasGroup() const { return EntityGroup != nullptr; }
		inline std::string GetName() const { return Name; }

		virtual void OnUpdate(float DeltaTime) = 0;
		virtual void OnCollide(BaseEntity* Other, CollisionFilter Filter) = 0;
		
		inline Vec2Int GetSize() const { return Size; }
		inline void SetSize(const Vec2Int& Size) { this->Size = Size; }

		inline void SetEnableRender(bool bEnable) { bRenderEnabled = bEnable; }
		inline bool IsRenderEnabled() const { return bRenderEnabled;}

		inline void SetEnableCollision(bool bEnable);
		inline bool IsCollisionEnabled() const { return bCollisionEnabled; }

		/** Get Position, if bNextRelevent, get position from next tick */
		inline Vec2Int GetPosition(bool bNextRelevent = false) const
		{
			if (bNextRelevent & bNextPositionRelevent) return NextPosition;
			return Position;
		}

		/** Set Position, instance should has Enabled Collision to process Sweep */
		inline void SetPosition(const Vec2Int& NewPosition, bool bSweep = false)
		{
			if (bCollisionEnabled & bSweep)
			{
				// Handle Position on next collision check
				NextPosition = NewPosition;
				bNextPositionRelevent = true;
				bPrevPositionRelevent = false;
				return;
			}

			Position = NewPosition;
		}

		inline void AddToCollisionFilter(BaseEntity* Collidable) { CollisionFilterList.push_back(Collidable); }
		inline void RemoveFromCollisionFilter(BaseEntity* Collidable) 
		{ 
			auto It = std::find(CollisionFilterList.begin(), CollisionFilterList.end(), Collidable);
			if (It != CollisionFilterList.end())
				CollisionFilterList.erase(It);
		}

	protected:
		// Collision Block ----------------------------------------------------------------------------------------------- //

		/** Raw check for two Boxed object collision. Should be accessible only form class SystemCollision */
		inline bool IsCollidingWith(const Vec2Int& Position, BaseEntity* Other, const Vec2Int& OtherPosition)
		{
			if (Other == nullptr) return false;

			Vec2Int OtherSize = Other->GetSize();

			if (Position.X < OtherPosition.X + OtherSize.X && Position.X + Size.X > OtherPosition.X &&
				Position.Y < OtherPosition.Y + OtherSize.Y && Position.Y + Size.Y > OtherPosition.Y)
				return true;
			else
				return false;
		}

		/** Handle Collidable Black/White list. Should be accessible only from class SystemCollision  */
		inline bool CanCollideWith(BaseEntity* Collidable, bool bCheckOtherFilterList = false)
		{
			std::vector<BaseEntity*>::iterator Iter;
			Iter = std::find(CollisionFilterList.begin(), CollisionFilterList.end(), Collidable);

			bool bIsInCollidableFilter = Iter != CollisionFilterList.end();

			bool bCanCollide = !(bIsInCollidableFilter ^ bCollisionFilterIsWhiteList); // XNOR, if 1 and 1 -> 1, elif 0 and 0 -> 1, else -> 0

			if (bCheckOtherFilterList)
				bCanCollide = bCanCollide && Collidable->CanCollideWith(this, false); // if check other, then 1 and 1 -> 1 else -> 0

			return bCanCollide;
		}

		inline bool IsPosGameBound(const Vec2Int& NewPosition)
		{
			auto Game = GetGame();
			const Vec2Int& BoundLeft = Game->GetGameBoundLeft();
			const Vec2Int& BoundRight = Game->GetGameBoundRight();
			
			if (NewPosition.X < BoundLeft.X) return false;
			if (NewPosition.X + Size.X > BoundRight.X) return false;
			if (NewPosition.Y < BoundLeft.Y) return false;
			if (NewPosition.Y + Size.Y > BoundRight.Y) return false;

			return true;
		}

		inline void SetPosBoundClamped(const Vec2Int& NewPosition)
		{
			auto Game = GetGame();
			const Vec2Int& BoundLeft = Game->GetGameBoundLeft();
			const Vec2Int& BoundRight = Game->GetGameBoundRight();

			Vec2Int FixedPos = NewPosition;

			// clamp x
			if (NewPosition.X < BoundLeft.X) FixedPos.X = BoundLeft.X;
			else if (NewPosition.X + Size.X > BoundRight.X) FixedPos.X = BoundLeft.X - Size.X;

			// clamp y
			if (NewPosition.Y < BoundLeft.X) FixedPos.Y = BoundLeft.Y;
			else if (NewPosition.Y + Size.Y > BoundRight.Y) FixedPos.Y = BoundRight.Y - Size.Y;

			// Set new position
			Position = FixedPos;
		}
		 
		inline void SetPosBlockClamped(const Vec2Int& NewPosition, BaseEntity* Blocker)
		{
			Vec2Int DeltaPos = NewPosition - Position;
			Vec2Int BlockerSize = Blocker->Size;
			Vec2Int BlockerPos = Blocker->Position;
			
			Vec2Int FixedPos = NewPosition;

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

		// Call only in class SystemCollision
		inline void HandleSweepPosition(const Vec2Int& NewPosition, const CollisionCheckResult& CollisionResult)
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

		// Collision Block End ------------------------------------------------------------------------------------------- //

	public:
		// Position meta info Block -------------------------------------------------------------------------------------- //

		/** Get center offset, offset = Size / 2 */
		inline Vec2Int GetCenterOffset() const { return Size / 2; }

		/** Get center position, CenterPos = Position + CenterOffset */
		inline Vec2Int GetCenterPosition() const { return Position + GetCenterOffset(); }

		/** Get side offset relative to CenterPos */
		inline Vec2Int GetSideOffset(Direction Side) const
		{
			Vec2Int SideOffset;

			switch (Side)
			{
			case Direction::RIGHT:
				SideOffset.X = Size.X / 2;
				break;
			case Direction::LEFT:
				SideOffset.X = -Size.X / 2;
				break;
			case Direction::DOWN:
				SideOffset.Y = Size.Y / 2;
				break;
			case Direction::UP:
				SideOffset.Y = -Size.Y / 2;
				break;
			}

			return SideOffset;
		}

		/** Get center point of chosen bounding box line, SidePos = CenterPos + SideOffset */
		inline Vec2Int GetSidePosition(Direction Side) const { return GetCenterPosition() + GetSideOffset(Side); }

		/** Get center point of opposite bounding box line, OppositeSidePos = CenterPos - SideOffset */
		inline Vec2Int GetOppositeSidePosition(Direction Side) const { return GetCenterPosition() - GetSideOffset(Side); }

		// Position meta info Block End ---------------------------------------------------------------------------------- //
	};
}
