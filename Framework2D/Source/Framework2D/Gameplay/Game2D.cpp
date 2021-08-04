#include <PCH_Framework.h>
#include "Game2D.h"

#include <Framework2D/Layers/Layer2D.h>
#include <Framework2D/Layers/LayerSystem.h>
#include <Framework2D/Layers/LayerGameplay.h>


namespace Framework2D {
	
	Game2D* Game2D::Instance = nullptr;

	Game2D::Game2D(const char* Title, unsigned int Width, unsigned int Height,
		const Vec2& GameBoundLeft, const Vec2& GameBoundRight)
		: Application(Title, Width, Height), GameBoundLeft(GameBoundLeft), GameBoundRight(GameBoundRight)
	{
		// create layers
		SystemLayer = new LayerSystem("SystemLayer");
		HUDLayer = new Layer2D("HUDLayer");
		MainLayer = new Layer2D("MainLayer");
		GameplayLayer = new LayerGameplay("GameplayLayer");

		PushLayer(MainLayer);
		PushLayer(GameplayLayer);
		PushOverlay(HUDLayer);
		PushOverlay(SystemLayer);
	}

	Game2D::~Game2D()
	{
		delete SystemLayer;
		delete GameplayLayer;
		delete CurrentGameMode;
		delete HUDLayer;
		delete MainLayer;
	}
	
	inline void Game2D::ChangeGameMode(GameMode* NewGameMode, bool bAutoStart)
	{
		auto PrevGM = CurrentGameMode;
		CurrentGameMode = NewGameMode;
		GameplayLayer->GM = NewGameMode;
		delete PrevGM;

		if (bAutoStart) NewGameMode->Start();
	}
}
