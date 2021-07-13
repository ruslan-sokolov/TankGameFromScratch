#pragma once

#include <Engine.h>
#include <EntryPoint.h>

#include <Framework2D/Initializer.h>

#include "Framework2D/Graphic2D/Layer2D.h"

namespace Framework2D {

	class Game2D : public Engine::Application
	{
		Layer2D* DebugLayer;
		Layer2D* HUDLayer;
		Layer2D* MainLayer;

	public:
		Game2D(const char* Title, unsigned int Width, unsigned int Height)
			: Application(Title, Width, Height)
		{
			// create layers
			DebugLayer = new Layer2D("DebugLayer");
			HUDLayer = new Layer2D("HUDLayer");
			MainLayer = new Layer2D("MainLayer");

			PushLayer(MainLayer);
			PushOverlay(DebugLayer);
			PushOverlay(HUDLayer);

			// framework initializer
			auto Initializer = CreateInitializer();
			Initializer->Init();
			delete Initializer;
		}

		~Game2D()
		{

		}

		inline Layer2D* GetDebugLayer() const { return DebugLayer; }
		inline Layer2D* GetHUDLayer() const { return HUDLayer; }
		inline Layer2D* GetMainLayer() const { return MainLayer; }
	};

	static Game2D* Game;
	static inline Game2D* GetGame() { return Game; }

}

Engine::Application* Engine::CreateApplication()
{
	return new Framework2D::Game2D("Tanki Game", 640, 480);
}
