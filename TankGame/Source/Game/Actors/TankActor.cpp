#include "TankActor.h"

#include <Game/Game.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	Tank::Tank(const std::string& Name, const Vec2& Position)
		: Actor(Name, Position)
	{
		// Enable collision
		SetEnableCollision(false);

		// Actor defaults
		Speed = 20.f;
		MoveAnimRate = 0.1f;

		// Create actor components
		SpriteComp_Up = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteUp" + Name, Position, MoveAnimRate, ResPath::T_TANK_UP_0, ResPath::T_TANK_UP_1);
		SpriteComp_Up->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Up->GetSprite()->SetEnableRender(false);

		SpriteComp_Down = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteDown" + Name, Position, MoveAnimRate, ResPath::T_TANK_DOWN_0, ResPath::T_TANK_DOWN_1);
		SpriteComp_Down->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Down->GetSprite()->SetEnableRender(false);
		
		SpriteComp_Left = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteLeft" + Name, Position, MoveAnimRate, ResPath::T_TANK_LEFT_0, ResPath::T_TANK_LEFT_1);
		SpriteComp_Left->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Left->GetSprite()->SetEnableRender(false);
		
		SpriteComp_Right = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteRight" + Name, Position, MoveAnimRate, ResPath::T_TANK_RIGHT_0, ResPath::T_TANK_RIGHT_1);
		SpriteComp_Right->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Right->GetSprite()->SetEnableRender(false);

		// Initialize actor size
		SetSize(SpriteComp_Up->GetSize());

		// Initialize tank direction
		SpriteComp_Current = SpriteComp_Up;
		ChangeDirection(Direction::UP);
	}

	void Tank::OnTick(float DeltaTime)
	{
		Move(DeltaTime);
	}

	void Tank::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{

	}

	inline EntityComponent<SpriteFlipFlop>* Tank::GetDirectionSpriteComp(Direction Dir)
	{
		switch (Dir)
		{
		case Direction::RIGHT: 
			return SpriteComp_Right;
		
		case Direction::DOWN:
			return SpriteComp_Down;
		
		case Direction::LEFT:
			return SpriteComp_Left;
		
		default:
			return SpriteComp_Up;
		}
	}

	inline void Tank::ChangeDirection(Direction DirectionTo)
	{
		CurrentDirection = DirectionTo;

		SpriteComp_Current->GetEntity()->SetEnableRender(false);
		SpriteComp_Current = GetDirectionSpriteComp(DirectionTo);
		SpriteComp_Current->GetEntity()->SetEnableRender(true);
	}

	inline void Tank::EnableMoveAnim(bool bEnable, Direction Dir)
	{
		auto SpriteComp = GetDirectionSpriteComp(Dir);
		SpriteComp->GetSprite()->SetAutoFlipFlopEnable(bEnable);
	}

	inline void Tank::Move(float DeltaTime)
	{
		if (!bCanMove) return;

		Vec2 DeltaPos = DirectionToVec2(CurrentDirection) * Speed * DeltaTime;
		Vec2 NewPos = GetPosition() + DeltaPos;
		SetPosition(NewPos, true);
	}

	void Tank::MoveBegin(Direction DirectionTo)
	{
		ChangeDirection(DirectionTo);
		EnableMoveAnim(true, DirectionTo);
		
		bCanMove = true;
	}

	void Tank::MoveEnd(Direction DirectionTo)
	{
		EnableMoveAnim(false, DirectionTo);

		if (DirectionTo == CurrentDirection) // execute only if last key pressed is last key released
			bCanMove = false;
	}

	void Tank::Fire()
	{
		GAME_LOG(info, "Tank {} fired!", GetName());
	}

}