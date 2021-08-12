#include <PCH_Framework.h>
#include "GameMode.h"

#include <Framework2D/Gameplay/Level.h>
#include <Framework2D/Gameplay/Controllers/PlayerController.h>
#include <Framework2D/Gameplay/Controllers/AIController.h>
#include <Framework2D/Gameplay/UI/HUD.h>

namespace Framework2D {

	GameMode::GameMode(Level* InLevel, PlayerController* InPlayerController, HUD* InHUD, AIController* InAIController)
		: m_Level(InLevel), m_PlayerController(InPlayerController), m_HUD(InHUD), m_AIController(InAIController)
	{
		Initialize();
	}

	GameMode::~GameMode() 
	{
	}

	inline void GameMode::Initialize()
	{
		m_Level->GM_Owner = this;
		m_PlayerController->GM_Owner = this;
		m_HUD->GM_Owner = this;
		m_AIController->GM_Owner = this;
	}

	inline void GameMode::Update(float DeltaTime)
	{
		switch (State)
		{
		case GMState::Start:
			StartInternal();
			break;

		case GMState::End:
			EndInternal();
			break;

		case GMState::Restart:
			RestartInternal();
			break;
		
		case GMState::Run:
			RunInternal(DeltaTime);
			break;
		}
	}

	inline void GameMode::RunInternal(float DeltaTime)
	{
		m_Level->Update(DeltaTime);
		m_HUD->Update(DeltaTime);

		m_PlayerController->OnTick(DeltaTime);
		m_AIController->OnTick(DeltaTime);

		OnTick(DeltaTime);
	}

	inline void GameMode::SetState(GMState NewState, bool bForce)
	{
		if (bForce)
		{
			State = NewState;
			return;
		}
		
		if (State == GMState::Restart)
		{
			return;
		}

		State = NewState;
	}

	inline void GameMode::StartInternal()
	{
 		m_Level->OnStart();
		m_PlayerController->OnStart();
		m_HUD->OnStart();
		m_AIController->OnStart();

		OnStart();

		SetState(GMState::Run);
		GAME_LOG(info, "_____GameMode::Run_____");
	}

	inline void GameMode::Start()
	{
		SetState(GMState::Start);
		GAME_LOG(info, "_____GameMode::Start_____");
	}

	inline void GameMode::RestartInternal()
	{
		OnRestart();

		Initialize();
		StartInternal();

		SetState(GMState::Run, true);
	}

	inline void GameMode::Restart()
	{
		SetState(GMState::Restart);
		GAME_LOG(info, "_____GameMode::Restart_____");
	}

	inline void GameMode::EndInternal()
	{
		m_Level->OnEnd();
		m_PlayerController->OnEnd();
		m_HUD->OnEnd();
		m_AIController->OnEnd();

		OnEnd();
	}

	inline void GameMode::End()
	{
		SetState(GMState::End);
		GAME_LOG(info, "_____GameMode::End_____");
	}
}
