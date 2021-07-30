#pragma once

#include <Framework2D/Gameplay/UI/HUD.h>

namespace Game {

	class TankiHUD : public Framework2D::HUD 
	{
	public:

		TankiHUD();

		virtual void OnTick(float DeltaTime) override;
	};

}