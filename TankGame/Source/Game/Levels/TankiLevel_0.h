#pragma once

#include <Framework2D/Gameplay/Level.h>

namespace Game {

	class TankiLevel_0 : public Framework2D::Level
	{
	public:

		TankiLevel_0();

		virtual void OnTick(float DeltaTime) override;

	};

}