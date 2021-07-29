#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	class GameMode;

	class FRAMEWORK2D_API PlayerController 
	{
		friend class GameMode;

		GameMode* GM_Owner = nullptr;

	public:
		virtual void OnTick(float DeltaTime) {}
	};

}
