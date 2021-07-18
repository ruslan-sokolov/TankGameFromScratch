#include <PCH_Framework.h>
#include "Game2D.h"

#include <Framework2D/Graphic2D/Layer2D.h>

namespace Framework2D {
	
	Game2D* Game2D::Instance = nullptr;

	Game2D::Game2D(const char* Title, unsigned int Width, unsigned int Height)
		: Application(Title, Width, Height)
	{
		// create layers
		DebugLayer = new Layer2D("DebugLayer");
		HUDLayer = new Layer2D("HUDLayer");
		MainLayer = new Layer2D("MainLayer");

		PushLayer(MainLayer);
		PushOverlay(DebugLayer);
		PushOverlay(HUDLayer);
	}

	Game2D::~Game2D()
	{
	}

}