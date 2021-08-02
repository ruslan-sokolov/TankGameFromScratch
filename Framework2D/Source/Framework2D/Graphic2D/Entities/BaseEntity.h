#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <Framework2D/Structs/Vectors.h>
#include <Framework2D/Structs/Direction.h>
#include <Framework2D/Structs/Collision.h>

#include <Framework2D/Gameplay/Game2D.h>

namespace Framework2D {

	class Group;
	class SystemCollision;

	class FRAMEWORK2D_API BaseEntity
	{
		friend class Group;
		friend class SystemCollision;
	
	protected:
		Group* EntityGroup;
		std::string Name;

		BaseEntity(const std::string& Name, const Vec2& Size = Vec2::VecZero, 
			const Vec2& Position = Vec2::VecZero, bool bRenderEnable = false) 
			: Name(Name), Size(Size), Position(Position), bRenderEnabled(bRenderEnable), EntityGroup(nullptr) {}

		bool bRenderEnabled;
		bool bCollisionEnabled = false;

		Vec2 Size;
		Vec2 Position;

		/** control if Collision Ignore Is BlackList or WhiteList */
		bool bCollisionFilterIsWhiteList = false;
		/** collision filter list, can work as blacklist or as whitelist */
		std::vector<BaseEntity*> CollisionFilterList = {};
		CollisionCheckResult LastCollisonResult;
		Vec2 NextPosition;
		Vec2 PrevPosition;
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
		
		inline Vec2 GetSize() const { return Size; }
		inline void SetSize(const Vec2& Size) { this->Size = Size; }

		inline void SetEnableRender(bool bEnable) { bRenderEnabled = bEnable; }
		inline bool IsRenderEnabled() const { return bRenderEnabled;}

		inline void SetEnableCollision(bool bEnable, bool bIsDynamic = false /* mean if object can move */);
		inline bool IsCollisionEnabled() const { return bCollisionEnabled; }

		/** Get Position, if bNextRelevent, get position from next tick */
		inline Vec2 GetPosition(bool bNextRelevent = false) const
		{
			if (bNextRelevent & bNextPositionRelevent) return NextPosition;
			return Position;
		}

		/** Set Position, instance should has Enabled Collision to process Sweep */
		inline void SetPosition(const Vec2& NewPosition, bool bSweep = false)
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
		inline bool IsCollidingWith(const Vec2& Position, BaseEntity* Other, const Vec2& OtherPosition)
		{
			if (Other == nullptr) return false;

			Vec2 OtherSize = Other->GetSize();

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

		inline bool IsPosGameBound(const Vec2& NewPosition)
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

		inline void SetPosBoundClamped(Vec2 NewPosition)
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
		 
		inline void SetPosBlockClamped(const Vec2& NewPosition, BaseEntity* Blocker)
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

		// Call only in class SystemCollision
		inline void HandleSweepPosition(const Vec2& NewPosition, const CollisionCheckResult& CollisionResult)
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
		inline Vec2 GetCenterOffset() const { return Size / 2; }

		/** Get center position, CenterPos = Position + CenterOffset */
		inline Vec2 GetCenterPosition() const { return Position + GetCenterOffset(); }

		/** Get side offset relative to CenterPos */
		inline Vec2 GetSideOffset(Direction Side) const
		{
			Vec2 SideOffset;

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
		inline Vec2 GetSidePosition(Direction Side) const { return GetCenterPosition() + GetSideOffset(Side); }

		/** Get center point of opposite bounding box line, OppositeSidePos = CenterPos - SideOffset */
		inline Vec2 GetOppositeSidePosition(Direction Side) const { return GetCenterPosition() - GetSideOffset(Side); }

		// Position meta info Block End ---------------------------------------------------------------------------------- //
	};
}
