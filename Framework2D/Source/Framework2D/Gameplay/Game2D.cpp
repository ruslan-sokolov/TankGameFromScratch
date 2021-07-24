#include <PCH_Framework.h>
#include "Game2D.h"

#include <Framework2D/Layers/Layer2D.h>
#include <Framework2D/Layers/LayerSystem.h>

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
	}

	Game2D::~Game2D()
	{
	}

}