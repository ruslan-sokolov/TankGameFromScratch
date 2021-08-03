#pragma once

#include <Framework2D/Gameplay/Level.h>
#include <Game/Game.h>

#include <Game/Actors/TankActor.h>


namespace Game {

	class TankiLevel_0 : public Framework2D::Level
	{
		Tank* PlayerTank;
		TankSpawnPoint PlayerSpawnPoint;

	public:
		TankiLevel_0();

		virtual void OnTick(float DeltaTime) override;

		Tank* GetPlayerTank() const { return PlayerTank; }

	};

}