#include "Game.h"

// debug
#include <Framework2D/Gameplay/Game2D.h>
#include <Framework2D/Graphic2D/Layer2D.h>
#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

#include <Framework2D/Graphic2D/Entities/SolidEntity.h>
#include <Framework2D/Graphic2D/Groups/GroupSolid.h>

#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>
#include <Framework2D/Graphic2D/Groups/GroupSprite.h>
// debug end

namespace Game {

	GameInitializer::GameInitializer()
	{
	}

	GameInitializer::~GameInitializer()
	{
	}

	void GameInitializer::Init()
	{
		Initializer::Init();
		GAME_LOG(LOG_WARN, "GameInitializer Init()");

		using namespace Framework2D;
		using namespace ResPath;

		// Load Textures
		ResourceLoader::LoadTexture(T_FLASHY_0);
		ResourceLoader::LoadTexture(T_TANK_EB_DOWN_0);

		// Prebind 32 textures
		ResourceLoader::PrebindTextures();

		// Register Shaders
		ResourceLoader::RegisterShader(ShaderType::QuadBatchColor, S_BATCH_COLOR);
		ResourceLoader::RegisterShader(ShaderType::QuadBatchTexture, S_BATCH_TEXTURE);

		// debug
		Game2D* game = GetGame();
		Layer2D* MainLayer = game->GetMainLayer();


		GroupSolid* GroupTest = new GroupSolid("TestGroupSolid");
		MainLayer->AddGroup(GroupTest);

		SolidEntity* SolidTest_0 = new SolidEntity("TestSolid", Vec4::YellowColor, VecInt2D::VecZero, VecInt2D(50), true);
		SolidEntity* SolidTest_1 = new SolidEntity("TestSolid2", Vec4::CyanColor, VecInt2D::VecZero, VecInt2D(20), true);
		SolidEntity* SolidTest_2 = new SolidEntity("TestSolid3", Vec4::MagentaColor, VecInt2D(200, 100), VecInt2D(70), true);

		GroupTest->AddSolid(SolidTest_0);
		GroupTest->AddSolid(SolidTest_1);
		GroupTest->AddSolid(SolidTest_2);

		GroupSprite* GroupTest_2 = new GroupSprite("TestGroupSprite");
		MainLayer->AddGroup(GroupTest_2);

		SpriteEntity* SpriteTest_0 = new SpriteEntity("TestSprite", T_FLASHY_0, VecInt2D(0, 0), VecInt2D(150, 50));
		SpriteEntity* SpriteTest_1 = new SpriteEntity("TestSprite2", T_TANK_EB_DOWN_0, VecInt2D(540, 380), VecInt2D(100, 100));

		GroupTest_2->AddSprite(SpriteTest_0);
		GroupTest_2->AddSprite(SpriteTest_1);

		// todo maybe create basic object?
		// todo maybe use shared ptr for obj?

		// debug end
	}


}

Framework2D::Initializer* Framework2D::CreateInitializer()
{
	return new Game::GameInitializer();
}