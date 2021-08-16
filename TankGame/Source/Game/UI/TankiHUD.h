#pragma once

#include <Framework2D/Gameplay/UI/HUD.h>
#include <Framework2D/Gameplay/UI/HUDCanvas.h>

namespace Game {

	using namespace Framework2D;

	class TankiHUD : public Framework2D::HUD 
	{
		CanvasIcon IconTankUI;
		Vec2 TankUIFirstPos;
		Vec2 TankUIOffset;
		uint8_t TankUIMax;
		uint8_t TankUIHorizontalMax;
		
		CanvasIcon IconDigits[10];
		Vec2 PlayerRespawnNumLocation;
		Vec2 DigitsOffset;
		uint8_t PlayerRespawnNumDigitMax;
		uint8_t PlayerRespawnNumDigitMin;

		CanvasIcon IconWinPlate;
		CanvasIcon IconLoosePlate;
		Vec2 PlateLocation;


		int EnemyTankDrawNum;
		
		int PlayerRespawnDrawNum; // will be converted to icon digits view

		bool bShouldDrawWinPlate;
		bool bShouldDrawLoosePlate;

		// internal draw handle

		inline void DrawEnemyTankIcons();
		inline void DrawPlayerRespawnNum();
		inline void DrawPlate();

	public:

		TankiHUD();

		// update draw info:

		inline void EnableWinPlate(bool bEnable) { bShouldDrawWinPlate = bEnable; }
		inline void EnablewLoosePlate(bool bEnable) { bShouldDrawLoosePlate = bEnable; }

		inline void UpdateTankDrawNum(int InEnemyTankNum) { EnemyTankDrawNum = InEnemyTankNum > TankUIMax ? TankUIMax : InEnemyTankNum; }

		inline void UpdatePlayerRespawnNum(int InPlayerRespawnNum) { PlayerRespawnDrawNum = InPlayerRespawnNum; }

		// draw
		virtual void DrawHUD(float DeltaTime) override;
	};

}