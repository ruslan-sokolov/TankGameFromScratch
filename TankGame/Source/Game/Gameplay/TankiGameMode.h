#pragma once

#include <Framework2D/Gameplay/GameMode.h>

namespace Game {

	class TankiPlayerController;
	class TankiLevel_0;
	class TankiHUD;
	class TankiAIController;

	class PhoenixBase;

	class TankiGameMode : public Framework2D::GameMode
	{
		TankiAIController* AITankController;
		TankiPlayerController* PlayerTankController;
		TankiLevel_0* BasicLevel;
		TankiHUD* CustomHUD;

		int PlayerRespawnNum;
		int EnemyTankToKill;
		bool bBaseIsDestroyed;

		bool bEndConditionIsWin;

	public:
		TankiAIController* GetCustomAIController() const { return AITankController; }
		TankiPlayerController* GetCustomPlayerTankController() const { return PlayerTankController; }
		TankiLevel_0* GetCustomBasicLevel() const { return BasicLevel; }
		TankiHUD* GetCustomHUD() const { return CustomHUD; }

		TankiGameMode();

		virtual void OnStart() override;
		virtual void OnEnd() override;
		virtual void OnRestart() override;

		/** called in base instance */
		void OnBaseDestroyed();

		/** called in tank instance */
		void OnEnemyTankKilled();

		/** called in tank player controller instane */
		void TryRespawnPlayerTank();
		
		/** Check game condition after each dependent event */
		inline void CheckLooseWinCondition();

	};

}