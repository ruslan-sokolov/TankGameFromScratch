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

	public:
		TankiAIController* GetCustomAIController() const { return AITankController; }
		TankiPlayerController* GetCustomPlayerTankController() const { return PlayerTankController; }
		TankiLevel_0* GetCustomBasicLevel() const { return BasicLevel; }
		TankiHUD* GetCustomHUD() const { return CustomHUD; }

		TankiGameMode();

		virtual void OnTick(float DeltaTime) override;
		virtual void OnStart() override;
		
		virtual void Restart() override;
		virtual void End() override;

		inline PhoenixBase* GetLevelPhoenixBase();

	};

}