#pragma once

#include <Framework2D/Gameplay/Controllers/AIController.h>

namespace Game {

	class TankiAIController : public Framework2D::AIController
	{
	public:

		TankiAIController();

		virtual void OnTick(float DeltaTime) override;
	};

}