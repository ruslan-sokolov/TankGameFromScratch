#pragma once

#include <Framework2D/Gameplay/Level.h>
#include <Game/Game.h>

namespace Game {

	class Tank;

	class TankiLevel_0 : public Framework2D::Level
	{
		Tank* PlayerTank;

	public:
		TankiLevel_0();

		virtual void OnTick(float DeltaTime) override;

		Tank* GetPlayerTank() const { return PlayerTank; }

	};

}