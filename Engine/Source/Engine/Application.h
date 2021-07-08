#pragma once

#include "PCH.h"
#include "Core.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

	private:
		std::unique_ptr<class Window> m_Window;
		bool bIsRunning = true;

	};

	Application* CreateApplication();
}
