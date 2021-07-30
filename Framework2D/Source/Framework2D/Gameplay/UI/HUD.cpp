#include <PCH_Framework.h>
#include "HUD.h"

#include "HUDElement.h"

namespace Framework2D {

	void HUD::Update(float DeltaTime)
	{
		for (auto& HUDElem : Elements) HUDElem->OnHUDElemTick(DeltaTime);
		OnTick(DeltaTime);
	}

	HUD::HUD()
	{
	}

	HUD::~HUD()
	{
		for (auto& HUDElem : Elements) delete HUDElem;
	}

}
