#include <PCH_Framework.h>
#include "Game2D.h"

#include <Framework2D/Layers/Layer2D.h>
#include <Framework2D/Layers/LayerSystem.h>

#include <Framework2D/Systems/SystemInput.h>

namespace Framework2D {
	
	Game2D* Game2D::Instance = nullptr;

	Game2D::Game2D(const char* Title, unsigned int Width, unsigned int Height,
		const VecInt2D& GameBoundLeft, const VecInt2D& GameBoundRight)
		: Application(Title, Width, Height), GameBoundLeft(GameBoundLeft), GameBoundRight(GameBoundRight)
	{
		// create layers
		SystemLayer = new LayerSystem("SystemLayer");
		HUDLayer = new Layer2D("HUDLayer");
		MainLayer = new Layer2D("MainLayer");

		PushLayer(MainLayer);
		PushOverlay(HUDLayer);
		PushOverlay(SystemLayer);

		SystemInput::BindKeyEvent(KEY_W, true, INPUT_CALLBACK(Game2D::MoveForward));
		
		SystemTimer::SetTimer(TimerHandle_1, TIMER_CALLBACK(Game2D::DelayedFunc), 6);
		SystemTimer::SetTimer(TimerHandle_2, TIMER_CALLBACK(Game2D::DelayedFuncLoop), 1, true);
	}

	Game2D::~Game2D()
	{
	}

	void Game2D::MoveForward()
	{
		GAME_LOG(warn, "MoveForward");
	}

	void Game2D::DelayedFunc()
	{
		GAME_LOG(warn, "Delayed func");
		SystemTimer::RemoveTimer(TimerHandle_2);
		//SystemInput::UnbindKeyEvent(KEY_W, true, INPUT_CALLBACK(Game2D::MoveForward));
	}

	void Game2D::DelayedFuncLoop()
	{
		GAME_LOG(warn, "Delayed func loop");
	}

}