#pragma once

#include <Framework2D.h>

namespace ResPath
{
	// Shaders path (starts with prefix "S_")

	constexpr auto S_BATCH_TEXTURE = "..\\Resources\\Shaders\\QuadBatchTexture.shader";
	constexpr auto S_BATCH_COLOR = "..\\Resources\\Shaders\\QuadBatchColor.shader";

	// Textures path (starts with prefix "T_")
	
	// Tank yellow
	constexpr auto T_TANK_DOWN_0 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_down_0.png";
	constexpr auto T_TANK_DOWN_1 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_down_1.png";
	constexpr auto T_TANK_UP_0 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_up_0.png";
	constexpr auto T_TANK_UP_1 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_up_1.png";
	constexpr auto T_TANK_LEFT_0 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_left_0.png";
	constexpr auto T_TANK_LEFT_1 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_left_1.png";
	constexpr auto T_TANK_RIGHT_0 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_right_0.png";
	constexpr auto T_TANK_RIGHT_1 = "..\\Resources\\Textures\\Tank\\tank0\\tank0_right_1.png";

	// Brick, full block has 16, four of each side
	constexpr auto T_BRICK_0 = "..\\Resources\\Textures\\Tank\\brick\\brick_frag_0.png";
	constexpr auto T_BRICK_1 = "..\\Resources\\Textures\\Tank\\brick\\brick_frag_1.png";
	constexpr auto T_BRICK_BASE = "..\\Resources\\Textures\\Tank\\brick\\brick_base.png";

	// Bullet
	constexpr auto T_BULLET_UP = "..\\Resources\\Textures\\Tank\\bullet\\bullet_u.png";
	constexpr auto T_BULLET_DOWN = "..\\Resources\\Textures\\Tank\\bullet\\bullet_d.png";
	constexpr auto T_BULLET_RIGHT = "..\\Resources\\Textures\\Tank\\bullet\\bullet_r.png";
	constexpr auto T_BULLET_LEFT = "..\\Resources\\Textures\\Tank\\bullet\\bullet_l.png";

	// Tank Base Enemy
	constexpr auto T_TANK_EB_DOWN_0 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_down_0.png";
	constexpr auto T_TANK_EB_DOWN_1 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_down_1.png";
	constexpr auto T_TANK_EB_UP_0 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_up_0.png";
	constexpr auto T_TANK_EB_UP_1 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_up_1.png";
	constexpr auto T_TANK_EB_LEFT_0 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_left_0.png";
	constexpr auto T_TANK_EB_LEFT_1 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_left_1.png";
	constexpr auto T_TANK_EB_RIGHT_0 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_right_0.png";
	constexpr auto T_TANK_EB_RIGHT_1 = "..\\Resources\\Textures\\Tank\\tank_enemy_base\\tank_e_b_right_1.png";

	// Base
	constexpr auto T_PHOENIX_PNG = "..\\Resources\\Textures\\Tank\\phoenix.png";

	// Boom
	constexpr auto T_BOOM_SMALL_0 = "..\\Resources\\Textures\\Tank\\boom\\boom_small_0.png";
	constexpr auto T_BOOM_SMALL_1 = "..\\Resources\\Textures\\Tank\\boom\\boom_small_1.png";
	constexpr auto T_BOOM_SMALL_2 = "..\\Resources\\Textures\\Tank\\boom\\boom_small_2.png";
	constexpr auto T_BOOM_BIG_0 = "..\\Resources\\Textures\\Tank\\boom\\boom_big_0.png";
	constexpr auto T_BOOM_BIG_1 = "..\\Resources\\Textures\\Tank\\boom\\boom_big_1.png";

	// Flashy
	constexpr auto T_FLASHY_0 = "..\\Resources\\Textures\\Tank\\flashy_0.png";
	constexpr auto T_FLASHY_1 = "..\\Resources\\Textures\\Tank\\flashy_1.png";

	// Boost
	constexpr auto T_BOOST_HP = "..\\Resources\\Textures\\Tank\\tank_hp_boost.png";

	// UI
	constexpr auto T_WON_UI = "..\\Resources\\Textures\\Tank\\UI\\GameOverWon.png";
	constexpr auto T_LOOSE_UI = "..\\Resources\\Textures\\Tank\\UI\\GameOverLoose.png";
	constexpr auto T_TANK_ICO_UI = "..\\Resources\\Textures\\Tank\\UI\\ui_enemy.png";

	constexpr auto T_UI_NUM_0 = "..\\Resources\\Textures\\Tank\\Num\\0.png";
	constexpr auto T_UI_NUM_1 = "..\\Resources\\Textures\\Tank\\Num\\1.png";
	constexpr auto T_UI_NUM_2 = "..\\Resources\\Textures\\Tank\\Num\\2.png";
	constexpr auto T_UI_NUM_3 = "..\\Resources\\Textures\\Tank\\Num\\3.png";
	constexpr auto T_UI_NUM_4 = "..\\Resources\\Textures\\Tank\\Num\\4.png";
	constexpr auto T_UI_NUM_5 = "..\\Resources\\Textures\\Tank\\Num\\5.png";
	constexpr auto T_UI_NUM_6 = "..\\Resources\\Textures\\Tank\\Num\\6.png";
	constexpr auto T_UI_NUM_7 = "..\\Resources\\Textures\\Tank\\Num\\7.png";
	constexpr auto T_UI_NUM_8 = "..\\Resources\\Textures\\Tank\\Num\\8.png";
	constexpr auto T_UI_NUM_9 = "..\\Resources\\Textures\\Tank\\Num\\9.png";
}

namespace GameConst
{
}

namespace Game {

	class GameInitializer : public Framework2D::Initializer
	{
	public:
		GameInitializer();
		~GameInitializer();

		void Init() override;
	};

}