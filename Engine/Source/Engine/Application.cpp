// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#include <PCH.h>
#include "Application.h"

#include <Platform/WindowsWindow.h>

namespace Engine {

	Application::Application(const char* Title, unsigned int Width, unsigned int Height)
	{
		m_Window = std::unique_ptr<class Window>(WindowsWindow::Create( { Title, Width, Height } ));
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
		T_Start = std::chrono::high_resolution_clock::now();
		T_Prev = T_Start;
		T_Next = T_Start;

		while (bIsRunning)
		{
			T_Prev = T_Next;
			T_Next = std::chrono::high_resolution_clock::now();
			DeltaTime = std::chrono::duration<float, ::std::ratio<1>>(T_Next - T_Prev).count();

			// Call layers update (forward direction)
			for (auto layer : Layers) layer->OnUpdate(DeltaTime);

			m_Window->OnUpdate();
		}
	}
}
