#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Engine/Events/KeyEvent.h>
#include <Engine/Events/MouseEvent.h>

namespace Framework2D
{
	class BaseEntity;

	/*
	 * This system handles game input
	 */
	class FRAMEWORK2D_API SystemInput
	{

	public:

		static void OnInputEvent(Engine::Event& e);

	};
}


