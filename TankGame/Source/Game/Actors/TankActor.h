#pragma once

#include <Framework2D/Gameplay/Actor/Actor.h>

#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>
#include <Framework2D/Gameplay/Actor/Components/HealthComponent.h>

namespace Game {

	using namespace Framework2D;


	struct TankSkin
	{
		const char* Up_0;
		const char* Up_1;
		const char* Down_0;
		const char* Down_1;
		const char* Right_0;
		const char* Right_1;
		const char* Left_0;
		const char* Left_1;

		static TankSkin PlayerBasicTankSkin;
		static TankSkin EnemyBasicTankSkin;
	};


	struct TankSpawnPoint
	{
		Vec2 SpawnPosition;
		Direction SpawnDirection = Direction::UP;
		Anchor SpawnAnchor = Anchor::TOP_LEFT;

		TankSpawnPoint() {}

		TankSpawnPoint(Vec2 SpawnPosition, Direction SpawnDirection, Anchor SpawnAnchor)
			: SpawnPosition(SpawnPosition), SpawnDirection(SpawnDirection), SpawnAnchor(SpawnAnchor) {}
		
		static TankSpawnPoint TopLeftSpawnPoint;
		static TankSpawnPoint TopRightSpawnPoint;
		static TankSpawnPoint BottomLeftSpawnPoint;
		static TankSpawnPoint BottomRightSpawnPoint;
		static TankSpawnPoint TopCenterSpawnPoint;
	};


	enum class TankType
	{
		None = -1,
		PlayerTank = 0,
		EnemyTank = 1
	};


	/*
	 * This class is represent main AI/Player controlled actor - tank
	 *
	 */
	class Tank : public Framework2D::Actor
	{
	public:
		/*
		 * Constructor should be called only from Level::SpawnActorFromClass() method;
		 * Constructor can initialize Actor Components;
		 */
		Tank(const std::string& Name, const Vec2& Position, 
			Direction StartDirection, float Speed, float MoveAnimRate, float Health, const TankSkin& Skin);
		
		// frame per frame logic, no need to call Framework2D::Actor implementation
		virtual void OnTick(float DeltaTime) override;
		virtual void OnDestroy() override;
		// HealthComp cb
		void OnDeath();

	protected:
		HealthComponent* HealthComp;

		// direction
		EntityComponent<SpriteFlipFlop>* SpriteComp_Up;
		EntityComponent<SpriteFlipFlop>* SpriteComp_Down;
		EntityComponent<SpriteFlipFlop>* SpriteComp_Left;
		EntityComponent<SpriteFlipFlop>* SpriteComp_Right;

		EntityComponent<SpriteFlipFlop>* SpriteComp_Current;
		Direction CurrentDirection;

		inline EntityComponent<SpriteFlipFlop>* GetDirectionSpriteComp(Direction Dir);
		inline void ChangeDirection(Direction DirectionTo);

		bool bCanMove = false;
		float Speed;

		// movement
		inline void Move(float DeltaTime);

		// movement anim
		float MoveAnimRate;
		inline void EnableMoveAnim(bool bEnable, Direction Dir);
		
		TankType Type = TankType::None;

	public:
		void MoveBegin(Direction DirectionTo);
		void MoveEnd(Direction DirectionTo);

		class Bullet* ActiveBullet = nullptr;
		void Fire();

		Direction GetDirection() const { return CurrentDirection; }
		TankType GetTankType() const { return Type; }
		bool IsPossesedByPlayerController() const { return Type == TankType::PlayerTank; }
		bool IsPossesedByAIController() const { return Type == TankType::EnemyTank; }

		static Tank* SpawnBasicTank(Level* Level, const TankSpawnPoint& Point, TankType Type);
		
		// if this value is true then on death tank will spawn pickable boost
		bool bDropPickableOnDeath = false;


		// debug
		void DebugHit();
	};
}
