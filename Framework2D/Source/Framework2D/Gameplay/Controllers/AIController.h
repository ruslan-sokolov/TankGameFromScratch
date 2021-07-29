#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {
	
	class GameMode;

	/*
	 * Base class to controll all of AI driven Actors;
	 * Should utilize one to many relationships;
	 */
	class FRAMEWORK2D_API AIController
	{
		friend class GameMode;

		GameMode* GM_Owner = nullptr;

		GameMode* GetGameMode() const { return GM_Owner; }

	public:
		virtual void OnTick(float DeltaTime) {}
	};

}
