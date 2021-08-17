#include "TankiGameMode.h"

#include "TankiPlayerController.h"
#include "TankiAIController.h"
#include <Game/UI/TankiHUD.h>
#include <Game/Levels/TankiLevel_0.h>
#include <Game/Actors/TankActor.h>

#include <Game/Game.h>

#include <Framework2D/Systems/SystemTimer.h>
#include <Framework2D/Systems/SystemCollision.h>
#include <Framework2D/Systems/SystemInput.h>


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

		PlayerRespawnNumMax = GameConst::PLAYER_TANK_RESPAWN_NUM;
		PlayerRespawnNum = PlayerRespawnNumMax;
		EnemyTankToKill = GameConst::TANK_SPAWN_NUM_DEFAULT;
		bBaseIsDestroyed = false;
		bEndConditionIsWin = false;
		bIsGameEnd = false;
	}

	void TankiGameMode::OnStart()
	{
		CustomHUD->UpdateTankDrawNum(EnemyTankToKill);
		CustomHUD->UpdatePlayerRespawnNum(PlayerRespawnNum);
	}

	void TankiGameMode::OnEnd()
	{
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
		 
		PlayerRespawnNum = PlayerRespawnNumMax;
		EnemyTankToKill = GameConst::TANK_SPAWN_NUM_DEFAULT;
		bBaseIsDestroyed = false;
		bEndConditionIsWin = false;
		bIsGameEnd = false;
	}

	void TankiGameMode::OnBaseDestroyed()
	{
		bBaseIsDestroyed = true;

		GAME_LOG(warn, "GM: BASE IS DESTROYED!!!");

		CheckLooseWinCondition();
	}

	void TankiGameMode::OnEnemyTankKilled()
	{
		CustomHUD->UpdateTankDrawNum(--EnemyTankToKill);

		GAME_LOG(warn, "GM: Enemy to kill left: {}", EnemyTankToKill);

		CheckLooseWinCondition();
	}

	void TankiGameMode::AddRespawnPoint(int Val)
	{
		PlayerRespawnNum += Val;
		
		// clamp
		if (PlayerRespawnNum >= PlayerRespawnNumMax)
			PlayerRespawnNum = PlayerRespawnNumMax;

		CustomHUD->UpdatePlayerRespawnNum(PlayerRespawnNum);

		GAME_LOG(info, "GM: Added RespawnPoint, Total: {}", PlayerRespawnNum);
	}

	void TankiGameMode::TryRespawnPlayerTank()
	{
		CustomHUD->UpdatePlayerRespawnNum(--PlayerRespawnNum);
		
		GAME_LOG(error, "GM: Player respawn num left: {}", PlayerRespawnNum);

		if (PlayerRespawnNum >= 0)
		{
			auto Tank = BasicLevel->SpawnPlayerTank();
			Tank->RespawnProtection_Activate();
			PlayerTankController->SetControlledTank(Tank);
		}

		CheckLooseWinCondition();
	}

	inline void TankiGameMode::CheckLooseWinCondition()
	{
		if (bIsGameEnd) return;

		if (PlayerRespawnNum <= -1 || bBaseIsDestroyed) 
		{
			bIsGameEnd = true;
			bEndConditionIsWin = false;

			CustomHUD->EnableWinPlate(true);
			GAME_LOG(warn, "GM: YOU WON!!!!");

			TimerHandle TimerHandle_Empty;
			SystemTimer::SetTimer(TimerHandle_Empty, TIMER_CALLBACK(GameMode::End), GameConst::RESTART_TIME);
		}
		else if (EnemyTankToKill <= 0)
		{
			bIsGameEnd = true;
			bEndConditionIsWin = true;
			
			CustomHUD->EnablewLoosePlate(true);
			GAME_LOG(warn, "GM: YOU LOOSE!!!");

			TimerHandle TimerHandle_Empty;
			SystemTimer::SetTimer(TimerHandle_Empty, TIMER_CALLBACK(GameMode::End), GameConst::RESTART_TIME);
		}
	}
}
