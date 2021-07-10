#pragma once

#include <Engine.h>
#include <Framework2D/Initializer.h>

namespace Framework2D {

	class MainLayer : public Engine::Layer
	{
	public:
		MainLayer()
			: Layer("MainLayer") {}

		void OnUpdate() override
		{

		}

		void OnAttach() override
		{

		}

		void OnDetach() override
		{

		}

		void OnEvent(Engine::Event& e) override
		{
			// debug
			GAME_LOG(LOG_INFO, "[Framework2D::MainLayer] OnEvent {0}", e);
		}
	};

	class MainLoop : public Engine::Application
	{
	public:
		MainLoop()
		{
			// create main layer
			PushLayer(new MainLayer());

			// framework initializer
			auto Initializer = CreateInitializer();
			Initializer->Init();
			delete Initializer;
		}

		~MainLoop()
		{

		}
	};

}

Engine::Application* Engine::CreateApplication()
{
	return new Framework2D::MainLoop();
}
