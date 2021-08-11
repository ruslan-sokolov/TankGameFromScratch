#pragma once

#include <Framework2D/Gameplay/Level.h>
#include <Game/Actors/TankActor.h>


namespace Game {

	// todo: to base TankiLevel class
	class TankiLevel_0 : public Framework2D::Level
	{
		Tank* PlayerTank;
		TankSpawnPoint PlayerSpawnPoint;
		class TankSpawner* EnemyTankSpawner;


	public:
		TankiLevel_0();

		virtual void OnStart() override;

		Tank* GetPlayerTank() const { return PlayerTank; }
		inline Tank* RespawnPlayerTank();

	};

}
