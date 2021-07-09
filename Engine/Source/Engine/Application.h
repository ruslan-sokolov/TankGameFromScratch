// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

#include "Core.h"
#include <Engine/Events/ApplicationEvent.h>
#include <Engine/LayerStack.h>

#include <memory>

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

	};

	Application* CreateApplication();

}

