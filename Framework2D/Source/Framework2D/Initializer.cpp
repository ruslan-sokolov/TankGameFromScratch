#include "PCH_Framework.h"
#include "Initializer.h"

#include <GL/glew.h>


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
	}
}