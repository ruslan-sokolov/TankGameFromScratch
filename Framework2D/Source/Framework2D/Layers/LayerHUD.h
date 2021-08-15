#pragma once

#include "Layer2D.h"


namespace Framework2D
{
	class LayerHUD : public Engine::Layer
	{
		class HUDCanvas* m_Canvas = nullptr;

	public:

		LayerHUD(const std::string& LayerName);
		~LayerHUD();

		void SetCanvas(HUDCanvas* Canvas) { m_Canvas = Canvas; }

		// draw canvas items
		void OnUpdate(float DeltaTime) override;
	};
}