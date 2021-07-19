// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#include <PCH.h>
#include "Application.h"

#include <Platform/WindowsWindow.h>

#include <Engine/Events/ApplicationEvent.h>
#include <Engine/Events/KeyEvent.h>

namespace Engine {

	Application::Application(const char* Title, unsigned int Width, unsigned int Height)
	{
		CustomWindow = std::unique_ptr<class Window>(WindowsWindow::Create( { Title, Width, Height } ));
		CustomWindow->SetEventCb(BIND_EVENT(Application::DistpatchEvents));
	}

	Application::~Application() {}
	
	void Application::DistpatchEvents(Event& e)
	{
		EventDistpatcher Distpatcher(e);
		Distpatcher.Dispatch<WindowCloseEvent>(BIND_EVENT(Application::OnWindowClose));
		Distpatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(Application::OnFullscreenKeyPressed));
		Distpatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT(Application::OnFullscreenKeyReleassed));

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

	bool Application::OnFullscreenKeyPressed(KeyPressedEvent& e)
	{
		switch (e.GetKeyCode())
		{
		case GLFW_KEY_ENTER:
			bIsEnterKeyPressed = true;
			break;

		case GLFW_KEY_LEFT_ALT:
		case GLFW_KEY_RIGHT_ALT:
			bIsAltKeyPressed = true;
			break;
		}

		if (bIsEnterKeyPressed && bIsAltKeyPressed)
		{
			CustomWindow->SetFullscreen(!CustomWindow->IsFullscreen());
			return true;
		}
		return false;
	}

	bool Application::OnFullscreenKeyReleassed(KeyReleasedEvent& e)
	{
		switch (e.GetKeyCode())
		{
		case GLFW_KEY_ENTER:
			bIsEnterKeyPressed = false;
			break;

		case GLFW_KEY_LEFT_ALT:
		case GLFW_KEY_RIGHT_ALT:
			bIsAltKeyPressed = false;
			break;
		}

		return false;
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

			CustomWindow->OnUpdate();
		}
	}

	inline float Application::GetWidth() const
	{
		return CustomWindow->GetWidth();
	}

	inline float Application::GetHeight() const
	{
		return CustomWindow->GetHeight();
	}
}
