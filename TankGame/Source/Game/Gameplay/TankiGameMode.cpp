#include "TankiGameMode.h"

#include "TankiPlayerController.h"
#include "TankiAIController.h"
#include <Game/UI/TankiHUD.h>
#include <Game/Levels/TankiLevel_0.h>
#include <Game/Actors/TankActor.h>

#include <Game/Game.h>

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

		PlayerRespawnNum = GameConst::PLAYER_TANK_RESPAWN_NUM;
		EnemyTankToKill = GameConst::TANK_SPAWN_NUM_DEFAULT;
		bBaseIsDestroyed = false;
		bEndConditionIsWin = false;
	}

	void TankiGameMode::OnStart()
	{
		// todo
	}

	void TankiGameMode::OnEnd()
	{
		if (bEndConditionIsWin)
		{
			GAME_LOG(trace, "GM: YOU WON!!!!");
			// todo show win plate
		}
		else
		{
			GAME_LOG(trace, "GM: YOU LOOSE!!!");
			// todo show loose plate
		}

		// inf loop here
		Restart();
	}

	void TankiGameMode::OnRestart()
	{
	}

	inline PhoenixBase* TankiGameMode::GetLevelPhoenixBase()
	{
		if (BasicLevel)
		{
			return BasicLevel->GetPlayerBase();
		}
		return nullptr;
	}

	void TankiGameMode::OnBaseDestroyed()
	{
		bBaseIsDestroyed = true;

		GAME_LOG(warn, "GM: BASE IS DESTROYED!!!");

		CheckLooseWinCondition();
	}

	void TankiGameMode::OnEnemyTankKilled()
	{
		--EnemyTankToKill;

		GAME_LOG(warn, "GM: Enemy to kill left: {}", EnemyTankToKill);

		CheckLooseWinCondition();
	}

	void TankiGameMode::TryRespawnPlayerTank()
	{
		--PlayerRespawnNum;

		GAME_LOG(error, "GM: Player respawn num left: {}", PlayerRespawnNum);

		if (PlayerRespawnNum >= 0)
		{
			auto Tank = BasicLevel->RespawnPlayerTank();
			PlayerTankController->SetControlledTank(Tank);
		}

		CheckLooseWinCondition();
	}

	inline void TankiGameMode::CheckLooseWinCondition()
	{
		if (PlayerRespawnNum <= -1 || bBaseIsDestroyed) 
		{
			bEndConditionIsWin = false;
			End();
		}
		else if (EnemyTankToKill <= 0)
		{
			bEndConditionIsWin = true;
			End();
		}
	}
}
