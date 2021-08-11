#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <vector>

namespace Framework2D {

	class GameMode;
	class HUDElement;

	class FRAMEWORK2D_API HUD
	{
		friend class GameMode;
		GameMode* GM_Owner = nullptr;
		// call OnTick for HUD and it's elements;
		void Update(float DeltaTime);

		std::vector<HUDElement*> Elements;

	public:
		HUD();
		virtual ~HUD();

		/** Called in GameMode Start() */
		virtual void OnStart() {};
		virtual void OnEnd() {};

		/** Called in GameMode Update() each frame */
		virtual void OnTick(float DeltaTime) {}
	};

}
