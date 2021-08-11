#include <PCH_Framework.h>
#include "Game2D.h"

#include <Framework2D/Layers/Layer2D.h>
#include <Framework2D/Layers/LayerSystem.h>
#include <Framework2D/Layers/LayerGameplay.h>
#include <Framework2D/Layers/Layer2DDebug.h>

namespace Framework2D {
	
	Game2D* Game2D::Instance = nullptr;

	Game2D::Game2D(const char* Title, unsigned int Width, unsigned int Height,
		const Vec2& GameBoundLeft, const Vec2& GameBoundRight)
		: Application(Title, Width, Height), GameBoundLeft(GameBoundLeft), GameBoundRight(GameBoundRight)
	{
		// create layers
		SystemLayer = new LayerSystem("SystemLayer");
		DebugLayer = new Layer2DDebug("DebugLayer");
		HUDLayer = new Layer2D("HUDLayer");
		MainLayer = new Layer2D("MainLayer");
		GameplayLayer = new LayerGameplay("GameplayLayer");

		PushLayer(MainLayer);
		PushLayer(GameplayLayer);
		PushOverlay(HUDLayer);
		PushOverlay(SystemLayer);
		PushOverlay(DebugLayer);
	}

	void Game2D::OnInitialize()
	{
		DebugLayer->OnInitialize();
	}

	Game2D::~Game2D()
	{
		delete SystemLayer;
		delete GameplayLayer;
		delete CurrentGameMode;
		delete HUDLayer;
		delete MainLayer;
		delete DebugLayer;
	}
	
	void Game2D::DragDebugSolid(const Vec2& Position, const Vec2& Size, const Vec4& Color, float Time)
	{
		ENGINE_ASSERT(DebugLayer, "DebugLayer is nullptr!!!");

		if (DebugLayer) DebugLayer->DrawDebugSolid(Position, Size, Color, Time);
	}

	void Game2D::DrawDebugBox(const Vec2& Position, const Vec2& Size, const Vec4& Color, float Time)
	{
		ENGINE_ASSERT(DebugLayer, "DebugLayer is nullptr!!!");

		if (DebugLayer) DebugLayer->DrawDebugBox(Position, Size, Color, Time);
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
