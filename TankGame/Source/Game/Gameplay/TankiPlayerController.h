#pragma once

#include <Framework2D/Gameplay/Controllers/PlayerController.h>

namespace Game {

	class Tank;

	class TankiPlayerController : public Framework2D::PlayerController
	{
		Tank* PlayerTank = nullptr;

	public:
		
		TankiPlayerController();
		~TankiPlayerController();

		virtual void OnTick(float DeltaTime);

		// input callbacks to bind in constructor
		void MoveForward();
		void MoveForwardStop();
		
		void MoveBackward();
		void MoveBackwardStop();

		void MoveLeft();
		void MoveLeftStop();

		void MoveRight();
		void MoveRightStop();

		void Fire();

		void SetControlledTank(Tank* TankToControl);
		Tank* GetControlledTank() const { return PlayerTank; }

	};
}