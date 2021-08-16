#include "TankiHUD.h"

#include <Game/Game.h>

namespace Game {
	using namespace ResPath;
	using namespace GameConst;

	TankiHUD::TankiHUD()
		: IconDigits{ 
			Canvas->MakeCanvasIcon(T_UI_NUM_0),
			Canvas->MakeCanvasIcon(T_UI_NUM_1),
			Canvas->MakeCanvasIcon(T_UI_NUM_2),
			Canvas->MakeCanvasIcon(T_UI_NUM_3),
			Canvas->MakeCanvasIcon(T_UI_NUM_4),
			Canvas->MakeCanvasIcon(T_UI_NUM_5),
			Canvas->MakeCanvasIcon(T_UI_NUM_6),
			Canvas->MakeCanvasIcon(T_UI_NUM_7),
			Canvas->MakeCanvasIcon(T_UI_NUM_8),
			Canvas->MakeCanvasIcon(T_UI_NUM_9) }
	{

		// for drawing enemy tanks icons in hud
		IconTankUI = Canvas->MakeCanvasIcon(T_TANK_ICO_UI);
		TankUIFirstPos =    { TANK_UI_FIRST_W, TANK_UI_FIRST_H };
		TankUIOffset =      { TANK_UI_OFFSET_W, TANK_UI_OFFSET_H };
		TankUIMax =           TANK_UI_MAX;
		TankUIHorizontalMax = TANK_UI_HORIZONTAL_MAX;
		
		PlayerRespawnNumLocation = { PLAYER_RESPAWN_NUM_W, PLAYER_RESPAWN_NUM_H };
		DigitsOffset = { UI_NUM_DIGIT_OFFSET, 0 };
		PlayerRespawnNumDigitMax = UI_NUM_DIGIT_MAX;
		PlayerRespawnNumDigitMin = UI_NUM_DIGIT_MIN;

		IconWinPlate = Canvas->MakeCanvasIcon(T_WON_UI);
		IconLoosePlate = Canvas->MakeCanvasIcon(T_LOOSE_UI);
		PlateLocation = { GAME_OVER_PLATE_W, GAME_OVER_PLATE_H };

		EnemyTankDrawNum = 0;
		PlayerRespawnDrawNum = 0;

		bShouldDrawWinPlate = false;
		bShouldDrawLoosePlate = false;
	}

	inline void TankiHUD::DrawEnemyTankIcons()
	{
		for (int i = 0; i < EnemyTankDrawNum; ++i)
		{
			Vec2 DrawPos = TankUIFirstPos;
			DrawPos.X += (i % TankUIHorizontalMax) * TankUIOffset.X;
			DrawPos.Y += (i / TankUIHorizontalMax) * TankUIOffset.Y;

			Canvas->DrawIcon(IconTankUI, DrawPos);
		}
	}

	inline void TankiHUD::DrawPlayerRespawnNum()
	{
		using Digits = std::vector<int>;

		auto GetDigits = [=]()
		{
			std::vector<int> DigitsOut;
			DigitsOut.reserve(9);

			int Val = PlayerRespawnDrawNum;

			while (Val > 0)
			{
				DigitsOut.emplace_back(Val % 10);  // insert from lesser to biger, so 1450 will be 0, 5, 4, 1
				Val = Val / 10;
			}

			if (DigitsOut.size() > PlayerRespawnNumDigitMax) // val has more digits then max digit num
			{
				DigitsOut = Digits(PlayerRespawnNumDigitMax, 9);  // if max 4: 1000 -> 999 if max 1: 10 -> 9
			}
			else if (DigitsOut.size() < PlayerRespawnNumDigitMin) // val has less digits then min digit num
			{
				for (int i = 0; i < PlayerRespawnNumDigitMin - DigitsOut.size(); ++i)
				{
					DigitsOut.push_back(0);  // insert zeros in digits array biggest index: if min 4: 45 -> 0045
				}
			}

			return DigitsOut;
		};

		Digits InDigits = GetDigits();

		Vec2 DigitPosLast = PlayerRespawnNumLocation + DigitsOffset * (InDigits.size() - 1); // digits are in reverse order, fix
		
		for (auto& Digit : InDigits)
		{
			auto& DigitIcon = IconDigits[Digit];

			Canvas->DrawIcon(DigitIcon, DigitPosLast);

			DigitPosLast -= DigitsOffset;
		}
		
		//// debug
		//for (int i = 0, size = sizeof(IconDigits) / sizeof(*IconDigits); i != size; ++i)
		//{
		//	Canvas->DrawIcon(IconDigits[i], DigitPos);
		//
		//	DigitPos.Y += DigitsOffset;
		//}
	}

	inline void TankiHUD::DrawPlate()
	{
		if (bShouldDrawLoosePlate)
		{
			Canvas->DrawIcon(IconWinPlate, PlateLocation);
		}
		else if (bShouldDrawWinPlate)
		{
			Canvas->DrawIcon(IconLoosePlate, PlateLocation);
		}
	}

	void TankiHUD::DrawHUD(float DeltaTime)
	{
		DrawEnemyTankIcons();
		DrawPlayerRespawnNum();
		DrawPlate();
	}

}