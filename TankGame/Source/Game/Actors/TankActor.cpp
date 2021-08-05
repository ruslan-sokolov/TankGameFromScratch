#include "TankActor.h"

#include <Framework2D/Gameplay/Level.h>
#include <Game/Actors/BulletActor.h>

namespace Game {

	TankSpawnPoint TankSpawnPoint::BottomLeftSpawnPoint(Vec2(GameConst::GAME_AREA_W0, GameConst::GAME_AREA_H1), Direction::UP, Anchor::BOTTOM_LEFT);
	TankSpawnPoint TankSpawnPoint::BottomRightSpawnPoint(Vec2(GameConst::GAME_AREA_W1, GameConst::GAME_AREA_H1), Direction::UP, Anchor::BOTTOM_RIGHT);
	TankSpawnPoint TankSpawnPoint::TopLeftSpawnPoint(Vec2(GameConst::GAME_AREA_W0, GameConst::GAME_AREA_H0), Direction::DOWN, Anchor::TOP_LEFT);
	TankSpawnPoint TankSpawnPoint::TopRightSpawnPoint(Vec2(GameConst::GAME_AREA_W1, GameConst::GAME_AREA_H0), Direction::DOWN, Anchor::TOP_RIGHT);
	TankSpawnPoint TankSpawnPoint::TopCenterSpawnPoint(Vec2(GameConst::GAME_AREA_W1 / 2, GameConst::GAME_AREA_H0), Direction::DOWN, Anchor::TOP);

	Tank::Tank(const std::string& Name, const Vec2& Position, 
		Direction StartDirection, float Speed, float MoveAnimRate, float Health, const TankSkin& Skin)
		: Actor(Name, Position), CurrentDirection(StartDirection), Speed(Speed), MoveAnimRate(MoveAnimRate)
	{
		// Enable collision
		EnableCollision(true);

		// Create actor components
		SpriteComp_Up = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteUp" + Name, Position, MoveAnimRate, Skin.Up_0, Skin.Up_1);
		SpriteComp_Up->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Up->GetSprite()->SetEnableRender(false);

		SpriteComp_Down = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteDown" + Name, Position, MoveAnimRate, Skin.Down_0, Skin.Down_1);
		SpriteComp_Down->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Down->GetSprite()->SetEnableRender(false);
		
		SpriteComp_Left = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteLeft" + Name, Position, MoveAnimRate, Skin.Left_0, Skin.Left_1);
		SpriteComp_Left->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Left->GetSprite()->SetEnableRender(false);
		
		SpriteComp_Right = new EntityComponent<SpriteFlipFlop>((Actor*)this, "FFSpriteRight" + Name, Position, MoveAnimRate, Skin.Right_0, Skin.Right_1);
		SpriteComp_Right->GetSprite()->SetAutoFlipFlopEnable(false);
		SpriteComp_Right->GetSprite()->SetEnableRender(false);

		HealthComp = new HealthComponent((Actor*)this);
		HealthComp->SetHealth(Health, true);

		// Initialize actor size
		SetSize(SpriteComp_Up->GetSize());

		// Initialize tank direction
		SpriteComp_Current = SpriteComp_Up;
		ChangeDirection(StartDirection);
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

		Vec2 DeltaPos = DirectionToVec2(CurrentDirection) * (Speed * DeltaTime);
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
		if (bPossesedByPlayer && ActiveBullet) return;  // player can only shoot if prev bullet is destroyed

		ActiveBullet = Bullet::SpawnBasicBullet(this);
	}

	Tank* Tank::SpawnBasicPlayerTank(Level* Level, const TankSpawnPoint& Point)
	{
		using namespace ResPath;
		using namespace GameConst;

		constexpr TankSkin PlayerTankSkin{ 
			T_TANK_UP_0, T_TANK_UP_1, 
			T_TANK_DOWN_0, T_TANK_DOWN_1, 
			T_TANK_RIGHT_0, T_TANK_RIGHT_1, 
			T_TANK_LEFT_0, T_TANK_LEFT_1 };

		ENGINE_ASSERT(Level, "SpawnBasicPlayerTank Level is nullptr!");

		Tank* PlayerTank = Level->SpawnActorFromClass<Tank>("PlayerTank", Point.SpawnPosition, Point.SpawnAnchor, 
			Point.SpawnDirection, TANK_BASIC_SPEED, TANK_BASIC_ANIM_SPEED, TANK_BASIC_HEALTH, PlayerTankSkin);
		
		PlayerTank->bPossesedByPlayer = true;

		return PlayerTank;
	}
}