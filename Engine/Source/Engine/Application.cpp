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

	Application::~Application()
	{
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDistpatcher Distpatcher(e);
		Distpatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));

		ENGINE_LOG(LOG_INFO, "{0}", e);
	}

	void Application::Run()
	{
		while (bIsRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}

