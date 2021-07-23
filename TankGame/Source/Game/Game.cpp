#include "Game.h"

#include <Framework2D.h>

#include <Framework2D/Graphic2D/Layer2D.h>
#include <Framework2D/Graphic2D/Render/ResourceLoader.h>
#include <Framework2D/Graphic2D/Render/Renderer.h>

#include <Framework2D/Graphic2D/Entities/SolidEntity.h>
#include <Framework2D/Graphic2D/Groups/GroupSolid.h>

#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>
#include <Framework2D/Graphic2D/Groups/GroupSprite.h>

namespace Game {

	class GameInitializer : public Framework2D::Initializer
	{
	public:
		void LoadTextures()
		{
			using namespace Framework2D;
			using namespace ResPath;

			ResourceLoader::LoadTexture({ T_TANK_DOWN_0
				, T_TANK_DOWN_1
				, T_TANK_UP_0
				, T_TANK_UP_1
				, T_TANK_LEFT_0
				, T_TANK_LEFT_1
				, T_TANK_RIGHT_0
				, T_TANK_RIGHT_1

				, T_BRICK_0
				, T_BRICK_1
				, T_BRICK_BASE

				, T_BULLET_UP
				, T_BULLET_DOWN
				, T_BULLET_RIGHT
				, T_BULLET_LEFT

				, T_TANK_EB_DOWN_0
				, T_TANK_EB_DOWN_1
				, T_TANK_EB_UP_0
				, T_TANK_EB_UP_1
				, T_TANK_EB_LEFT_0
				, T_TANK_EB_LEFT_1
				, T_TANK_EB_RIGHT_0
				, T_TANK_EB_RIGHT_1

				, T_PHOENIX_PNG

				, T_BOOM_SMALL_0
				, T_BOOM_SMALL_1
				, T_BOOM_SMALL_2
				, T_BOOM_BIG_0
				, T_BOOM_BIG_1

				, T_FLASHY_0
				, T_FLASHY_1

				, T_BOOST_HP

				, T_WON_UI
				, T_LOOSE_UI
				, T_TANK_ICO_UI

				, T_UI_NUM_0
				, T_UI_NUM_1
				, T_UI_NUM_2
				, T_UI_NUM_3
				, T_UI_NUM_4
				, T_UI_NUM_5
				, T_UI_NUM_6
				, T_UI_NUM_7
				, T_UI_NUM_8
				, T_UI_NUM_9
				
				});
		}

		void RegisterShaders()
		{
			using namespace Framework2D;
			using namespace ResPath;

			// Register Shaders
			ResourceLoader::RegisterShader(ShaderType::QuadBatchColor, S_BATCH_COLOR);
			ResourceLoader::RegisterShader(ShaderType::QuadBatchTexture, S_BATCH_TEXTURE);

			// Preset Shader uniforms.
			auto shader = ResourceLoader::GetShader(ShaderType::QuadBatchColor);
			shader->Bind();
			shader->SetUniformMat4f("u_ViewProjModel", RendererStatics::ProjViewModel);
			shader->Unbind();

			shader = ResourceLoader::GetShader(ShaderType::QuadBatchTexture);
			shader->Bind();
			shader->SetUniformMat4f("u_ViewProjModel", RendererStatics::ProjViewModel);

			std::vector<int> TexSlotArr;
			int TexSlotNum = Texture::GetMaxTextureBind() + 1;
			TexSlotArr.reserve(TexSlotNum );
			for (int i = 0; i < TexSlotNum; ++i) TexSlotArr.push_back(i);
			shader->SetUniform1iv("u_Textures", TexSlotNum, TexSlotArr.data());

			shader->Unbind();
		}

		void Init() override
		{
			using namespace Framework2D;
			using namespace ResPath;

			Initializer::Init();
			GAME_LOG(LOG_WARN, "Game::GameInitializer Init()");

			RegisterShaders();
			LoadTextures();

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

			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", "12312", VecInt2D(0, 0), VecInt2D(64, 64), Vec4::BlueColor));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite2", T_TANK_EB_DOWN_0, VecInt2D(0, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite3", T_TANK_EB_DOWN_1, VecInt2D(16, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite4", T_TANK_EB_DOWN_0, VecInt2D(32, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite5", T_TANK_UP_1, VecInt2D(48, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_LEFT_0, VecInt2D(64, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_LEFT_1, VecInt2D(80, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_RIGHT_0, VecInt2D(96, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_RIGHT_1, VecInt2D(112, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BRICK_0, VecInt2D(132, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_RIGHT_1, VecInt2D(148, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BRICK_BASE, VecInt2D(164, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BULLET_UP, VecInt2D(180, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BULLET_DOWN, VecInt2D(196, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BULLET_RIGHT, VecInt2D(216, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BULLET_LEFT, VecInt2D(220, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_DOWN_0, VecInt2D(226, 0), 0, Vec4::GreenColor));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_DOWN_1, VecInt2D(248, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_UP_0, VecInt2D(260, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_UP_1, VecInt2D(280, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_RIGHT_0, VecInt2D(300, 0), 0, Vec4::CyanColor));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_RIGHT_1, VecInt2D(400, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_RIGHT_1, VecInt2D(432, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BOOM_SMALL_0, VecInt2D(448, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BOOM_SMALL_1, VecInt2D(464, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BOOM_SMALL_2, VecInt2D(500, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BOOM_BIG_0, VecInt2D(512, 0), 0, Vec4::RedColor));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BOOM_BIG_1, VecInt2D(532, 200), 0, Vec4::YellowColor));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_FLASHY_0, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_FLASHY_1, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_BOOST_HP, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_WON_UI, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_LOOSE_UI, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_ICO_UI, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_0, VecInt2D(540, 100)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_1, VecInt2D(540, 200)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_2, VecInt2D(540, 300)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_3, VecInt2D(200, 100)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_4, VecInt2D(300, 200)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_5, VecInt2D(540, 300)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_6, VecInt2D(540, 100)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_7, VecInt2D(540, 200)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_8, VecInt2D(240, 300)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_9, VecInt2D(140, 290)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_UI_NUM_4, VecInt2D(300, 220)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_RIGHT_1, VecInt2D(540, 0)));
			GroupTest_2->AddSprite(new SpriteEntity("TestSprite", T_TANK_EB_RIGHT_1, VecInt2D(540, 0)));

			// todo fix nullptrs in Group.Entities
		}
	};

}

Framework2D::Initializer* Framework2D::CreateInitializer()
{
	return new Game::GameInitializer();
}

Engine::Application* Engine::CreateApplication()
{
	auto App = Framework2D::CreateGame("Tanki From Shet", 640, 480);

	auto Initializer = Framework2D::CreateInitializer();
	Initializer->Init();
	delete Initializer;

	return App;
}
