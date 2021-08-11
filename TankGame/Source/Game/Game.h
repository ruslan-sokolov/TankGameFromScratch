#pragma once

namespace ResPath
{
	// Shaders path (starts with prefix "S_")

	constexpr auto S_BATCH_TEXTURE = "..\\Resources\\Shaders\\QuadBatchTexture.shader";
	constexpr auto S_BATCH_COLOR = "..\\Resources\\Shaders\\QuadBatchColor.shader";

	// Textures path (starts with prefix "T_")
	
	// Background
	constexpr auto T_BG = "..\\Resources\\Textures\\Tank\\BG.png";

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
	// game geometric params

	constexpr auto WINDOW_W = 640;
	constexpr auto WINDOW_H = 480;

	constexpr auto GAME_AREA_OFFSET_W = 64;
	constexpr auto GAME_AREA_OFFSET_H = 32;

	constexpr auto GAME_AREA_W = 208 * 2;
	constexpr auto GAME_AREA_H = 208 * 2;

	constexpr auto GAME_AREA_W0 = GAME_AREA_OFFSET_W;
	constexpr auto GAME_AREA_W1 = GAME_AREA_OFFSET_W + GAME_AREA_W;

	constexpr auto GAME_AREA_H0 = GAME_AREA_OFFSET_H;
	constexpr auto GAME_AREA_H1 = GAME_AREA_OFFSET_H + GAME_AREA_H;

	constexpr auto GAME_AREA_MID_W = GAME_AREA_W / 2 + GAME_AREA_OFFSET_W;
	constexpr auto GAME_AREA_MID_H = GAME_AREA_H / 2 + GAME_AREA_OFFSET_H;

	constexpr auto GAME_CHUNK_W = 16 * 2;
	constexpr auto GAME_CHUNK_H = 16 * 2;

	constexpr auto TANK_W = 13 * 2;
	constexpr auto TANK_H = 13 * 2;

	// game gameplay params

	constexpr auto TANK_BASIC_SPEED = 100.0f;  // pixels / sec
	constexpr auto TANK_BASIC_ANIM_SPEED = 0.1f;  // sprite_flip time in sec
	constexpr auto TANK_BASIC_HEALTH = 1.0f;

	constexpr auto BULLET_BASIC_SPEED = 400.0f;  // pixels / sec
	constexpr auto BULLET_BASIC_DAMAGE = 1.0f;

	constexpr auto BRICK_BASIC_HEALTH = 1.0f;

	constexpr auto TANK_SPAWN_NUM_DEFAULT = 20;
	constexpr auto TANK_SPAWN_RATE_DEFAULT = 3.0f; // sec

	constexpr auto PLAYER_TANK_RESPAWN_NUM = 5;

	constexpr auto ENEMY_BASIC_FIRE_RATE_MIN = 1.0f;  // sec
	constexpr auto ENEMY_BASIC_FIRE_RATE_MAX = 2.0f;  // sec
	constexpr auto ENEMY_AI_CHANGE_DIRECTION_RATE_MIN = 1.0f; // sec
	constexpr auto ENEMY_AI_CHANGE_DIRECTION_RATE_MAX = 1.3f; // sec

	constexpr auto BOOM_SMALL_ANIM_SPEED = 0.05f; // sec
	constexpr auto BOOM_BIG_ANIM_SPEED = 0.06f; // sec
	
	constexpr int FLASHY_ARRAY_DEFAULT[] = { 4, 11, 18 }; // sec
	constexpr int FLASHY_ARRAY_DEFAULT_SIZE = sizeof FLASHY_ARRAY_DEFAULT / sizeof * FLASHY_ARRAY_DEFAULT;

	constexpr auto FLASHY_ANIM_SPEED = 0.1f; // sec
	constexpr auto RESPAWN_PROTECTION_TIME = 1.0f;  // sec
	
	constexpr auto HP_BOOSTER_VAL = 1.0f;  //

	constexpr auto RESTART_TIME = 3.0f;  // sec

	constexpr bool BLUE_ON_BLUE = false; // if true -> allow friendly fire

	// ui geometric params

	constexpr auto GAME_OVER_PLATE_W = 200;
	constexpr auto GAME_OVER_PLATE_H = 225;

	constexpr auto TANK_UI_FIRST_W = 496;
	constexpr auto TANK_UI_FIRST_H = 496;
	constexpr auto TANK_UI_OFFSET_W = 16;
	constexpr auto TANK_UI_OFFSET_H = 16;
	constexpr auto TANK_UI_MAX = 20;
	constexpr auto TANK_UI_HORIZONTAL_MAX = 2;

	constexpr auto PLAYER_RESPAWN_NUM_W = 514;
	constexpr auto PLAYER_RESPAWN_NUM_H = 274;
	constexpr auto UI_NUM_DIGIT_OFFSET = 16;

}
