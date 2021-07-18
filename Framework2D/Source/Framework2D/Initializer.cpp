#include "PCH_Framework.h"
#include "Initializer.h"

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

// debug
#include <Framework2D/Gameplay/Game2D.h>
#include <Framework2D/Graphic2D/Entities/SolidEntity.h>
#include <Framework2D/Graphic2D/Groups/GroupSolid.h>
#include <Framework2D/Graphic2D/Layer2D.h>
// debug end

namespace Framework2D {

	Initializer::Initializer()
		: bIsGlewInitialized(false)
	{
	
	}

	Initializer::~Initializer()
	{

	}

	void Initializer::Init()
	{
		ENGINE_LOG(info, "Framework2D::Initializer::Init()");

		// this need to be called in every dll
		if (!bIsGlewInitialized)
		{
			int SuccessGLEWInit = glewInit() == GLEW_OK;
			ENGINE_ASSERT(SuccessGLEWInit, "Could not initialize GLEW!");
			bIsGlewInitialized = true;
		}
		
		// Load Textures
		ResourceLoader::LoadTexture("../Resources/Textures/sun_pic.png");
		ResourceLoader::LoadTexture("../Resources/Textures/UE_Logo.png");
		
		// Register Shaders
		ResourceLoader::RegisterShader(ShaderType::QuadBatchColor, "../Resources/Shaders/QuadBatchColor.shader");
		ResourceLoader::RegisterShader(ShaderType::QuadBatchTexture, "../Resources/Shaders/QuadBatchTexture.shader");

		// debug
		// todo: test sprite entity
		
		Game2D* game = GetGame();
		Layer2D* MainLayer = game->GetMainLayer();

		GroupSolid* GroupTest = new GroupSolid("TestGroup");
		MainLayer->AddGroup(GroupTest);

		SolidEntity* SolidTest_0 = new SolidEntity("TestSolid", Vec4::YellowColor, VecInt2D::VecZero, VecInt2D(50), true);
		SolidEntity* SolidTest_1 = new SolidEntity("TestSolid", Vec4::CyanColor, VecInt2D::VecZero, VecInt2D(20), true);
		SolidEntity* SolidTest_2 = new SolidEntity("TestSolid", Vec4::MagentaColor, VecInt2D(200, 100), VecInt2D(70), true);

		GroupTest->AddSolid(SolidTest_0);
		GroupTest->AddSolid(SolidTest_1);
		GroupTest->AddSolid(SolidTest_2);

		// todo maybe create basic object?
		// todo maybe use shared ptr for obj?
		
		// debug end
	}
}