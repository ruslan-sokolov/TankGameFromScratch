#include "PCH_Framework.h"
#include "Initializer.h"

#include <GL/glew.h>
#include <Framework2D/Graphic2D/Render/Renderer.h>
#include <Framework2D/Gameplay/Game2D.h>

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

		Game2D* Game = GetGame();
		RendererStatics::Init(Game->GetWidth(), Game->GetHeight());
	}
}
