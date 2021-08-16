#include <PCH_Framework.h>

#include "HUD.h"

#include "HUDCanvas.h"

#include <Framework2D/Gameplay/Game2D.h>
#include <Framework2D/Layers/LayerHUD.h>

namespace Framework2D {

	inline void HUD::Update(float DeltaTime)
	{
		DrawHUD(DeltaTime);
	}

	HUD::HUD()
	{
		// creating default canvas
		Canvas = new HUDCanvas();
		Canvas->HUD_Owner = this;
		Elements.emplace_back(Canvas);

		if (auto Game = GetGame())
		{
			if (auto HUDLayer = Game->GetHUDLayer())
			{
				HUDLayer->SetCanvas(Canvas);
			}
			else
			{
				ENGINE_ASSERT(false, "HUD::HUD() Game2D::GetHUDLayer() == nullptr!");
			}
		}
		else
		{
			ENGINE_ASSERT(false, "HUD::HUD() GetGame() == nullptr!");
		}
	}

	HUD::~HUD()
	{
		// on delete release canvas in HUDLayer
		if (auto Game = GetGame())
		{
			if (auto HUDLayer = Game->GetHUDLayer())
			{
				HUDLayer->SetCanvas(nullptr);
			}
		}

		for (auto& HUDElem : Elements) delete HUDElem;
	}

}
