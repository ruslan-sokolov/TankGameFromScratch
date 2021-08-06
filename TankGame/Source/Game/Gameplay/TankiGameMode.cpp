#include "TankiGameMode.h"

#include "TankiPlayerController.h"
#include "TankiAIController.h"
#include <Game/UI/TankiHUD.h>
#include <Game/Levels/TankiLevel_0.h>
#include <Game/Actors/TankActor.h>

namespace Game {

	// todo: looks nasty, fix that later on
	TankiGameMode::TankiGameMode()
		: GameMode(new TankiLevel_0, new TankiPlayerController, new TankiHUD, new TankiAIController)
	{
		BasicLevel = static_cast<TankiLevel_0*>(GetLevel());
		CustomHUD = static_cast<TankiHUD*>(GetHUD());
		PlayerTankController = static_cast<TankiPlayerController*>(GetPlayerController());
		AITankController = static_cast<TankiAIController*>(GetAIController());

		// Pass Tank To Player Controller
		Tank* PlayerTank = BasicLevel->GetPlayerTank();
		PlayerTankController->SetControlledTank(PlayerTank);
	}

	void TankiGameMode::OnTick(float DeltaTime)
	{

	}

	void TankiGameMode::OnStart()
	{

	}

	void TankiGameMode::Restart()
	{
		GameMode::Restart();
	}

	void TankiGameMode::End()
	{
		GameMode::End();
	}

	inline PhoenixBase* TankiGameMode::GetLevelPhoenixBase()
	{
		if (BasicLevel)
		{
			return BasicLevel->GetPlayerBase();
		}
		return nullptr;
	}
}
