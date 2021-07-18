#pragma once

#include "Engine.h"
#include "Framework2D/Framework2DAPI.h"

namespace Framework2D {

	class Layer2D;

	class FRAMEWORK2D_API Game2D : public Engine::Application
	{
		Layer2D* DebugLayer;
		Layer2D* HUDLayer;
		Layer2D* MainLayer;

		friend Game2D* CreateGame(const char* Title, unsigned int Width, unsigned int Height);
		Game2D(const char* Title, unsigned int Width, unsigned int Height);

	public:
		~Game2D();

		inline Layer2D* GetDebugLayer() const { return DebugLayer; }
		inline Layer2D* GetHUDLayer() const { return HUDLayer; }
		inline Layer2D* GetMainLayer() const { return MainLayer; }

		static Game2D* Instance;
	};

	inline Game2D* GetGame() { return Game2D::Instance; }
	inline Game2D* CreateGame(const char* Title, unsigned int Width, unsigned int Height)
	{
		Game2D::Instance = new Game2D(Title, Width, Height);
		return Game2D::Instance;
	}
}