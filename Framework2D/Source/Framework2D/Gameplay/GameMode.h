#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <memory>

namespace Framework2D
{
	class Level;
	class PlayerController;
	class HUD;
	class AIController;

	class FRAMEWORK2D_API GameMode
	{
		std::unique_ptr<Level> m_Level;
		std::unique_ptr<PlayerController> m_PlayerController;
		std::unique_ptr<HUD> m_HUD;
		std::unique_ptr<AIController> m_AIController;

	public:
		GameMode(Level* InLevel, PlayerController* InPlayerController, 
			HUD* InHUD, AIController* InAIController);
		virtual ~GameMode();

		// todo: fix
		//Level* GetLevel() const { return m_Level.get(); }
		//PlayerController* GetPlayerController() const { return m_PlayerController.get(); }
		//HUD* GetHUD() const { return m_HUD.get(); }
		//AIController* GetAIController() const { return m_AIController.get(); }

		// todo: start game
		// todo: end game
		// todo: restart level
	};
}
