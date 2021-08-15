#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <vector>

namespace Framework2D {

	class GameMode;
	class HUDElement;
	class HUDCanvas;

	class FRAMEWORK2D_API HUD
	{
		friend GameMode;
		
		// call OnTick for HUD and it's elements;
		inline void Update(float DeltaTime);

	protected:
		GameMode* GM_Owner = nullptr;
		
		std::vector<HUDElement*> Elements;
		HUDCanvas* Canvas;

	public:
		HUD();
		virtual ~HUD();

		/** Called in GameMode Start() */
		virtual void OnStart() {};
		virtual void OnEnd() {};

		/** Called in GameMode Update() each frame */
		virtual void DrawHUD(float DeltaTime) {}
	};

}
