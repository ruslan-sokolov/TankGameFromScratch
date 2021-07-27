#include <PCH_Framework.h>
#include "GameMode.h"

#include <Framework2D/Gameplay/Level.h>
#include <Framework2D/Gameplay/Controllers/PlayerController.h>
#include <Framework2D/Gameplay/Controllers/AIController.h>
#include <Framework2D/Gameplay/UI/HUD.h>

namespace Framework2D {

	GameMode::GameMode(Level* InLevel, PlayerController* InPlayerController,
		HUD* InHUD, AIController* InAIController)
	//	: m_Level(std::make_unique<Level>(InLevel)),
	//	m_PlayerController(std::make_unique<PlayerController>(InPlayerController)),
	//	m_HUD(std::make_unique<HUD>(InHUD))
	{
	}
	
	GameMode::~GameMode() 
	{
	}

}
