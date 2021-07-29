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

	class FRAMEWORK2D_API GameMode
	{
		std::unique_ptr<Level> m_Level;
		std::unique_ptr<PlayerController> m_PlayerController;
		std::unique_ptr<HUD> m_HUD;
		std::unique_ptr<AIController> m_AIController;

		friend class LayerGameplay;
		// called in LayerGameplay will tick for Level, HUD, PlayerContoller, AIController
		inline void Update(float DeltaTime);

	public:
		GameMode(Level* InLevel, PlayerController* InPlayerController, HUD* InHUD, 
			AIController* InAIController);

		// destructor called in Game2D
		// on gamemode change all shit should be deleted
		virtual ~GameMode();

		Level* GetLevel() const { return m_Level.get(); }
		PlayerController* GetPlayerController() const { return m_PlayerController.get(); }
		HUD* GetHUD() const { return m_HUD.get(); }
		AIController* GetAIController() const { return m_AIController.get(); }

		inline void Start();
		inline void Restart();
		inline void End();
	};
}
