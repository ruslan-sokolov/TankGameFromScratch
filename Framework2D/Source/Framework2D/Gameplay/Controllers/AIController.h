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
	
	protected:
		GameMode* GM_Owner = nullptr;


	public:
		AIController();
		virtual ~AIController();

		GameMode* GetGameMode() const { return GM_Owner; }

		/** Called in GameMode Start() */
		virtual void OnStart() {};
		virtual void OnEnd() {};

		/** Called in GameMode Update() each frame */
		virtual void OnTick(float DeltaTime) {}
	};

}
