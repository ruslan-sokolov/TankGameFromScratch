#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	class HUD;

	class FRAMEWORK2D_API HUDElement
	{
		friend class HUD;
		HUD* HUD_Owner = nullptr;

		virtual void OnHUDElemTick(float DeltaTime) {}
	};

}
