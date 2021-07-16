#include "PCH_Framework.h"
#include "Initializer.h"

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

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
	}
}