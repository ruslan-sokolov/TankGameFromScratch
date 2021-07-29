#pragma once

#include "Engine.h"
#include "Framework2D/Framework2DAPI.h"

#include "Framework2D/Structs/Vectors.h"

#include "GameMode.h"

namespace Framework2D {

	class LayerSystem;
	class Layer2D;
	class LayerGameplay;

	class FRAMEWORK2D_API Game2D : public Engine::Application
	{
		// Engine layers
		LayerSystem* SystemLayer;
		Layer2D* HUDLayer;
		Layer2D* MainLayer;
		LayerGameplay* GameplayLayer;

		// powered by Unreal Engine underhood hehe)
		GameMode* CurrentGameMode = nullptr;

		// 2D Game Gameplay boundaries
		const VecInt2D GameBoundLeft;
		const VecInt2D GameBoundRight;

		// function for creating Game2D instance
		friend Game2D* CreateGame(const char* Title, unsigned int Width, unsigned int Height,
			const VecInt2D& GameBoundLeft, const VecInt2D& GameBoundRight);
		
		Game2D(const char* Title, unsigned int Width, unsigned int Height, 
			const VecInt2D& GameBoundLeft, const VecInt2D& GameBoundRight);

	public:
		inline ~Game2D();

		inline LayerSystem* GetSystemLayer() const { return SystemLayer; }
		inline Layer2D* GetHUDLayer() const { return HUDLayer; }
		inline Layer2D* GetMainLayer() const { return MainLayer; }
		inline LayerGameplay* GetGameplayLayer() const { return GameplayLayer; }

		inline const VecInt2D& GetGameBoundLeft() const { return GameBoundLeft; }
		inline const VecInt2D& GetGameBoundRight() const { return GameBoundRight; }


		inline GameMode* GetCurrentGameMode() const { return CurrentGameMode; }
		inline void ChangeGameMode(GameMode* NewGameMode, bool bAutoStart = true);

		static Game2D* Instance;
	};

	// Scripting usefull functions

	inline Game2D* GetGame() { return Game2D::Instance; }
	
	inline GameMode* GetGM() { Game2D::Instance ? Game2D::Instance->GetCurrentGameMode() : nullptr; }
	
	inline Level* GetLevel() { if (auto GM = GetGM()) GM->GetLevel(); }
	
	inline PlayerController* GetPlayerController() { if (auto GM = GetGM()) GM->GetLevel(); }
	
	inline HUD* GetHUD() { if (auto GM = GetGM()) GM->GetHUD(); }
	
	inline AIController* GetAIController() { if (auto GM = GetGM()) GM->GetAIController(); }

	//

	inline Game2D* CreateGame(const char* Title, unsigned int Width, unsigned int Height, 
		const VecInt2D& GameBoundLeft, const VecInt2D& GameBoundRight)
	{
		Game2D::Instance = new Game2D(Title, Width, Height, GameBoundLeft, GameBoundRight);
		return Game2D::Instance;
	}
}
