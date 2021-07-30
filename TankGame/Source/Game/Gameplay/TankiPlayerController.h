#pragma once

#include <Framework2D/Gameplay/Controllers/PlayerController.h>

namespace Game {

	class TankiPlayerController : public Framework2D::PlayerController
	{
	public:

		TankiPlayerController();

		virtual void OnTick(float DeltaTime);

	};
}