#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	class GameMode;

	class Actor;

	/*
	 * This is base class for player controller, this class gives ability to actor to respond on input;
	 * Player controller is not Actor like in UE, it's stores in GameMode;
	 * And GameMode calls OnTick for PlayerController;
	 * For input binding you can use SystemInput Callbacks;
	 */
	class FRAMEWORK2D_API PlayerController 
	{
		friend class GameMode;
	
	protected:
		GameMode* GM_Owner = nullptr;

		Actor* ControlledActor = nullptr;

	public:
		PlayerController();
		virtual ~PlayerController();

		void SetControlledActor(Actor* ActorToControl) { ControlledActor = ActorToControl; }
		Actor* GetControlledActor() const { return ControlledActor; }

		GameMode* GetGameMode() const { return GM_Owner; }

		/** Called in GameMode Start() */
		virtual void OnStart() {};

		/** Called in GameMode Update() each frame */
		virtual void OnTick(float DeltaTime) {}
	};

}
