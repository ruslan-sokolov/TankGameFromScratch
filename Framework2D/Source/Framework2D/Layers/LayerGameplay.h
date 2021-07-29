#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Engine.h>

namespace Framework2D {

	class Game2D;
	class GameMode;

	/*
	 * Engine Layer to update gameplay objects
     */
	class FRAMEWORK2D_API LayerGameplay : public Engine::Layer
	{
		friend class Game2D;
		GameMode* GM = nullptr;

	public:
		LayerGameplay(const std::string& LayerName);
		~LayerGameplay();

		void OnUpdate(float DeltaTime) override;
	};

}
