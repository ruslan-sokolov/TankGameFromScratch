#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <memory>

namespace Framework2D
{
	class Level;
	class PlayerController;
	class HUD;
	class AIController;

	class LayerGameplay;

	enum class GMState
	{
		Prepartation = 0,
		Start = 1,
		Run = 2,
		End = 3,
		Restart = 4
	};

	class FRAMEWORK2D_API GameMode
	{
		GMState State = (GMState)0;
		GMState OldState = (GMState)0;

		friend class LayerGameplay;
		// called in LayerGameplay will tick for Level, HUD, PlayerContoller, AIController and GM itself
		inline void Update(float DeltaTime);

		inline void SetState(GMState NewState, bool bForce = false);

		inline void RunInternal(float DeltaTime);
		inline void StartInternal();
		inline void EndInternal();
		inline void RestartInternal();

	protected:
		Level* m_Level;
		PlayerController* m_PlayerController;
		HUD* m_HUD;
		AIController* m_AIController;

	protected:
		/** add GM ref to  Level, PC, HUD, AICon, etc.*/
		inline void Initialize();

	public:
		GameMode(Level* InLevel, PlayerController* InPlayerController, HUD* InHUD, 
			AIController* InAIController);

		// destructor called in Game2D
		// on gamemode change all shit should be deleted
		virtual ~GameMode();

		Level* GetLevel() const { return m_Level; }
		PlayerController* GetPlayerController() const { return m_PlayerController; }
		HUD* GetHUD() const { return m_HUD; }
		AIController* GetAIController() const { return m_AIController; }

		void Start();
		void Restart();
		void End();

		virtual void OnTick(float DeltaTime) {}

		inline GMState GetState() const { return State; }

	protected:
		/** BeginPlay kinda but only in one exemplar */
		virtual void OnStart() {}
		/** End Current Level */
		virtual void OnEnd() {}
		virtual void OnRestart() {}
	};
}
