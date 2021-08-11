#pragma once

#include <Framework2D/Gameplay/Level.h>
#include <Game/Actors/TankActor.h>


namespace Game {

	// todo: to base TankiLevel class
	class TankiLevel_0 : public Framework2D::Level
	{
		Tank* PlayerTank;
		TankSpawnPoint PlayerSpawnPoint;
		class PhoenixBase* PlayerBase;
		class TankSpawner* EnemyTankSpawner;


	public:
		TankiLevel_0();

		virtual void OnStart() override;

		Tank* GetPlayerTank() const { return PlayerTank; }
		PhoenixBase* GetPlayerBase() const { return PlayerBase; }
		TankSpawner* GetEnemySpawner() const { return EnemyTankSpawner; }

		inline Tank* RespawnPlayerTank();

	};

}
