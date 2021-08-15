#include <PCH_Framework.h>
#include "LayerHUD.h"

#include <Framework2D/Gameplay/UI/HUDCanvas.h>

namespace Framework2D {

	LayerHUD::LayerHUD(const std::string& LayerName)
	{
	}

	LayerHUD::~LayerHUD()
	{
	}

	void LayerHUD::OnUpdate(float DeltaTime)
	{
		if (m_Canvas) m_Canvas->DrawItems();
	}
}