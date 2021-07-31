#include "TankiPlayerController.h"

#include <Framework2D/Systems/SystemInput.h>
#include <Game/Actors/TankActor.h>

namespace Game {

	TankiPlayerController::TankiPlayerController()
	{
		// Bind input callbacks
		SystemInput::BindKeyEvent(KEY_W, true, INPUT_CALLBACK(TankiPlayerController::MoveForward));
		SystemInput::BindKeyEvent(KEY_W, false, INPUT_CALLBACK(TankiPlayerController::MoveForwardStop));
		SystemInput::BindKeyEvent(KEY_S, true, INPUT_CALLBACK(TankiPlayerController::MoveBackward));
		SystemInput::BindKeyEvent(KEY_S, false, INPUT_CALLBACK(TankiPlayerController::MoveBackwardStop));
		SystemInput::BindKeyEvent(KEY_A, true, INPUT_CALLBACK(TankiPlayerController::MoveLeft));
		SystemInput::BindKeyEvent(KEY_A, false, INPUT_CALLBACK(TankiPlayerController::MoveLeftStop));
		SystemInput::BindKeyEvent(KEY_D, true, INPUT_CALLBACK(TankiPlayerController::MoveRight));
		SystemInput::BindKeyEvent(KEY_D, false, INPUT_CALLBACK(TankiPlayerController::MoveRightStop));
	}

	TankiPlayerController::~TankiPlayerController()
	{
		// Unbind input callbacks
		SystemInput::UnbindKeyEvent(KEY_W, true, INPUT_CALLBACK(TankiPlayerController::MoveForward));
		SystemInput::UnbindKeyEvent(KEY_W, false, INPUT_CALLBACK(TankiPlayerController::MoveForwardStop));
		SystemInput::UnbindKeyEvent(KEY_S, true, INPUT_CALLBACK(TankiPlayerController::MoveBackward));
		SystemInput::UnbindKeyEvent(KEY_S, false, INPUT_CALLBACK(TankiPlayerController::MoveBackwardStop));
		SystemInput::UnbindKeyEvent(KEY_A, true, INPUT_CALLBACK(TankiPlayerController::MoveLeft));
		SystemInput::UnbindKeyEvent(KEY_A, false, INPUT_CALLBACK(TankiPlayerController::MoveLeftStop));
		SystemInput::UnbindKeyEvent(KEY_D, true, INPUT_CALLBACK(TankiPlayerController::MoveRight));
		SystemInput::UnbindKeyEvent(KEY_D, false, INPUT_CALLBACK(TankiPlayerController::MoveRightStop));
	}

	void TankiPlayerController::OnTick(float DeltaTime)
	{
	}

	void TankiPlayerController::MoveForward()
	{
		if (PlayerTank) PlayerTank->MoveBegin(Direction::UP);
	}

	void TankiPlayerController::MoveForwardStop()
	{
		if (PlayerTank) PlayerTank->MoveEnd(Direction::UP);
	}

	void TankiPlayerController::MoveBackward()
	{
		if (PlayerTank) PlayerTank->MoveBegin(Direction::DOWN);
	}

	void TankiPlayerController::MoveBackwardStop()
	{
		if (PlayerTank) PlayerTank->MoveEnd(Direction::DOWN);
	}

	void TankiPlayerController::MoveLeft()
	{
		if (PlayerTank) PlayerTank->MoveBegin(Direction::LEFT);
	}

	void TankiPlayerController::MoveLeftStop()
	{
		if (PlayerTank) PlayerTank->MoveEnd(Direction::LEFT);
	}

	void TankiPlayerController::MoveRight()
	{
		if (PlayerTank) PlayerTank->MoveBegin(Direction::RIGHT);
	}

	void TankiPlayerController::MoveRightStop()
	{
		if (PlayerTank) PlayerTank->MoveEnd(Direction::RIGHT);
	}

	void TankiPlayerController::Fire()
	{
		if (PlayerTank) PlayerTank->Fire();
	}

	void TankiPlayerController::SetControlledTank(Tank* TankToControl)
	{
		PlayerTank = TankToControl;
		SetControlledActor(TankToControl);
	}
}