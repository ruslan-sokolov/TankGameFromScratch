#include "TankiGameMode.h"

#include "TankiPlayerController.h"
#include "TankiAIController.h"
#include <Game/UI/TankiHUD.h>
#include <Game/Levels/TankiLevel_0.h>

namespace Game {

	// todo: looks nasty, fix that later on
	TankiGameMode::TankiGameMode()
		: GameMode(new TankiLevel_0, new TankiPlayerController, new TankiHUD, new TankiAIController)
	{
		BasicLevel = static_cast<TankiLevel_0*>(GetLevel());
		CustomHUD = static_cast<TankiHUD*>(GetHUD());
		PlayerTankController = static_cast<TankiPlayerController*>(GetPlayerController());
		AITankController = static_cast<TankiAIController*>(GetAIController());
	}

	void TankiGameMode::OnTick(float DeltaTime)
	{

	}

	void TankiGameMode::Start()
	{
		GameMode::Start();
	}

	void TankiGameMode::Restart()
	{
		GameMode::Restart();
	}

	void TankiGameMode::End()
	{
		GameMode::End();
	}
}
