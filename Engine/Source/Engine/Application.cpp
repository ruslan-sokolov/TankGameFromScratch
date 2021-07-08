#include "PCH.h"
#include "Application.h"

#include <Platform/WindowsWindow.h>
#include <GLFW/glfw3.h>

namespace Engine {

	Application::Application()
	{
		m_Window = std::unique_ptr<class Window>(WindowsWindow::Create());
	}

	Application::~Application()
	{
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

