#include "TankActor.h"

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	Tank::Tank(const std::string& Name, const VecInt2D& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		SetEnableCollision(true);

		// Actor defaults
		Speed = 20.f;
		MoveAnimRate = 0.1f;

		// Create actor components
		SpriteComp_Up = new EntityComponent<SpriteFlipFlop>((Actor*)this, Name, Position, MoveAnimRate, ResPath::T_TANK_UP_0, ResPath::T_TANK_UP_1);
		SpriteComp_Up->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Up->GetSprite()->SetEnableRender(false);

		SpriteComp_Down = new EntityComponent<SpriteFlipFlop>((Actor*)this, Name, Position, MoveAnimRate, ResPath::T_TANK_DOWN_0, ResPath::T_TANK_DOWN_1);
		SpriteComp_Down->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Down->GetSprite()->SetEnableRender(false);
		
		SpriteComp_Left = new EntityComponent<SpriteFlipFlop>((Actor*)this, Name, Position, MoveAnimRate, ResPath::T_TANK_LEFT_0, ResPath::T_TANK_LEFT_1);
		SpriteComp_Left->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Left->GetSprite()->SetEnableRender(false);
		
		SpriteComp_Right = new EntityComponent<SpriteFlipFlop>((Actor*)this, Name, Position, MoveAnimRate, ResPath::T_TANK_RIGHT_0, ResPath::T_TANK_RIGHT_1);
		SpriteComp_Right->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Right->GetSprite()->SetEnableRender(false);

		// Initialize actor size
		SetSize(SpriteComp_Up->GetSize());

		// Tank initialization
		SpriteComp_Current = SpriteComp_Up;
		SetNextDirectionSprite(Direction::UP);
		ChangeCurrentDirectionSprite();

	}

	void Tank::OnTick(float DeltaTime)
	{
		Move(DeltaTime);
	}

	void Tank::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{

	}

	inline void Tank::SetNextDirectionSprite(Direction DirectionTo)
	{
		if (DirectionTo == NextDirection) return;

		NextDirection = DirectionTo;

		switch (NextDirection)
		{
		case Direction::RIGHT:
			SpriteComp_Next = SpriteComp_Right;
			break;
		case Direction::DOWN:
			SpriteComp_Next = SpriteComp_Down;
			break;
		case Direction::LEFT:
			SpriteComp_Next = SpriteComp_Left;
			break;
		case Direction::UP:
			SpriteComp_Next = SpriteComp_Up;
			break;
		}
	}

	inline void Tank::ChangeCurrentDirectionSprite()
	{
		SpriteComp_Current->GetEntity()->SetEnableRender(false);
		
		CurrentDirection = NextDirection;
		SpriteComp_Current = SpriteComp_Next;

		SpriteComp_Next->GetEntity()->SetEnableRender(true);
	}

	inline void Tank::PlayMoveAnim()
	{
		SpriteComp_Current->GetSprite()->SetAutoFlipFlopEnable(true);
	}

	inline void Tank::StopMoveAnim()
	{
		SpriteComp_Current->GetSprite()->SetAutoFlipFlopEnable(false);
	}

	inline void Tank::Move(float DeltaTime)
	{
		if (!bCanMove) return;

		if (NextDirection != CurrentDirection && bPrevPositionRelevent)
		{
			SetPosition(PrevPosition);
		}
		else
		{
			VecInt2D DeltaPos = DirectionToVec(CurrentDirection) * (((Speed * DeltaTime) + 1));
			VecInt2D NewPos = GetPosition() + DeltaPos;
			SetPosition(NewPos, true);
		}
	}

	void Tank::MoveBegin(Direction DirectionTo)
	{
		SetNextDirectionSprite(DirectionTo);
		ChangeCurrentDirectionSprite();
		PlayMoveAnim();
		bCanMove = true;
	}

	void Tank::MoveEnd(Direction DirectionTo)
	{
		if (DirectionTo != NextDirection) return; // do not execute when two key are pressed then on of them is released

		bCanMove = false;
		StopMoveAnim();
	}

	void Tank::Fire()
	{
		GAME_LOG(info, "Tank {} fired!", GetName());
	}

}