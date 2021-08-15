#include "TankiGameMode.h"

#include "TankiPlayerController.h"
#include "TankiAIController.h"
#include <Game/UI/TankiHUD.h>
#include <Game/Levels/TankiLevel_0.h>
#include <Game/Actors/TankActor.h>

#include <Game/Game.h>

#include <Framework2D/Systems/SystemTimer.h>

// debug
#include <Framework2D/Systems/SystemCollision.h>
#include <Framework2D/Systems/SystemInput.h>
#include <Framework2D/Layers/Layer2D.h>


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
			GAME_LOG(warn, "GM: YOU WON!!!!");
			// todo show win plate
		}
		else
		{
			GAME_LOG(warn, "GM: YOU LOOSE!!!");
			// todo show loose plate
		}

		Restart();
	}

	void TankiGameMode::OnRestart()
	{
		SystemTimer::RemoveAllTimers();
		SystemCollision::ClearCheckCollisionSet();
		SystemInput::RemoveAllBinds();

		
		delete PlayerTankController;
		PlayerTankController = new TankiPlayerController();
		m_PlayerController = PlayerTankController;
		
		delete AITankController;
		AITankController = new TankiAIController;
		m_AIController = AITankController;
		
		delete BasicLevel;
		BasicLevel = new TankiLevel_0();
		m_Level = BasicLevel;
		
		delete CustomHUD;
		CustomHUD = new TankiHUD();
		m_HUD = CustomHUD;

		// Pass Tank To Player Controller
		Tank* PlayerTank = BasicLevel->GetPlayerTank();
		PlayerTankController->SetControlledTank(PlayerTank);
		 
		PlayerRespawnNum = GameConst::PLAYER_TANK_RESPAWN_NUM;
		EnemyTankToKill = GameConst::TANK_SPAWN_NUM_DEFAULT;
		bBaseIsDestroyed = false;
		bEndConditionIsWin = false;
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

	void TankiGameMode::AddRespawnPoint(int Val)
	{
		PlayerRespawnNum += Val;
		GAME_LOG(info, "GM: Added RespawnPoint, Total: {}", PlayerRespawnNum);
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
