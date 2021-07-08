#pragma once

#include "Core.h"

#include <Engine/Events/ApplicationEvent.h>

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

		void OnEvent(Event& e);

	private:
		std::unique_ptr<class Window> m_Window;
		bool bIsRunning = true;

		inline bool OnWindowClose(WindowCloseEvent& e)
		{
			ENGINE_LOG(LOG_WARN, "Success distpatch to WindowClose.");
			bIsRunning = false;
			return true;
		}
	};

	Application* CreateApplication();
}
