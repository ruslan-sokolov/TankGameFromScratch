// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#include <PCH.h>
#include "Application.h"

#include <Platform/WindowsWindow.h>
#include <GLFW/glfw3.h>

namespace Engine {

	Application::Application()
	{
		m_Window = std::unique_ptr<class Window>(WindowsWindow::Create());
		m_Window->SetEventCb(BIND_EVENT(Application::OnEvent));
	}

	Application::~Application() {}
	
	void Application::OnEvent(Event& e)
	{
		EventDistpatcher Distpatcher(e);
		Distpatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));

		// Call layers event callback (backward direction)
		for (auto it = Layers.end(); it != Layers.begin(); )
		{
			Layer& layer = *(*--it);
			layer.OnEvent(e);
			if (e.IsHandled()) break;
		}
	}
	
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		ENGINE_LOG(LOG_WARN, "Success distpatch to WindowClose.");
		bIsRunning = false;
		return true;
	}

	void Application::Run()
	{
		while (bIsRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// Call layers update (forward direction)
			for (auto layer : Layers) layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
}
