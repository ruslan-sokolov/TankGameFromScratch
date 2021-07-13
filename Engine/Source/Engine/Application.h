// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

#include "Core.h"
#include <Engine/Events/ApplicationEvent.h>
#include <Engine/LayerStack.h>

#include <memory>
#include <chrono>

namespace Engine {

	class ENGINE_API Application
	{
		std::unique_ptr<class Window> m_Window;
		bool bIsRunning = true;
		
		bool OnWindowClose(class WindowCloseEvent& e);

	protected:
		LayerStack Layers;

	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		inline void PushLayer(Layer* layer) { Layers.PushLayer(layer); }
		inline void PushOverlay(Layer* layer) { Layers.PushOverlay(layer); }

	private:
		std::chrono::steady_clock::time_point T_Start;
		std::chrono::steady_clock::time_point T_Prev;
		std::chrono::steady_clock::time_point T_Next;
		float DeltaTime;

	public:
		inline float GetDeltaTime() { return DeltaTime; }
		float GetElapsedTime() { return std::chrono::duration<float, std::milli>(T_Next - T_Start).count(); }

	};

	Application* CreateApplication();

}

