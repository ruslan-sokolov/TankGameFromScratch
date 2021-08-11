#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <Framework2D/Structs/Vectors.h>
#include <Framework2D/Structs/Direction.h>
#include <Framework2D/Structs/Anchor.h>

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

		CollisionType Collision = CollisionType::CT_Static;
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

		inline void EnableCollision(CollisionType Type = CollisionType::CT_Static);
		inline void DisableCollision();
		inline bool IsCollisionEnabled() const { return bCollisionEnabled; }
		inline bool IsCollisionDynamic() const { return bCollisionEnabled && (Collision == CollisionType::CT_Dynamic || Collision == CollisionType::CT_Projectile); }
		
		// if projectile very fast ( it can trevel through one corner of game area to another)
		// then it's should be very dynamic to collide with something in the way
		inline bool IsCollisionVeryDynamic() const { return bCollisionEnabled && Collision == CollisionType::CT_Projectile; }
		inline bool IsLastTimeCollisionPositive() const { return LastCollisonResult.bCollided; }
		inline CollisionCheckResult GetLastCollisionResult() const { return LastCollisonResult; }

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

		// Collision Block ----------------------------------------------------------------------------------------------- //
	public:
		/** Raw check for two Boxed object collision. Should be accessible only form class SystemCollision */
		inline bool IsCollidingWith(BaseEntity* Other, const Vec2& OtherPosition);

		/** Handle Collidable Black/White list. Should be accessible only from class SystemCollision  */
		inline bool CanCollideWith(BaseEntity* Collidable, bool bCheckOtherFilterList = false);

		/** Check if entity bound in game area setted in Game2D */
		inline bool IsPosGameBound(const Vec2& NewPosition);

	protected:
		inline void SetPosBoundClamped(Vec2 NewPosition);
		 
		inline void SetPosBlockClamped(const Vec2& NewPosition, BaseEntity* Blocker);

		// Call only in class SystemCollision
		inline void HandleSweepPosition(const Vec2& NewPosition, const CollisionCheckResult& CollisionResult);

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
