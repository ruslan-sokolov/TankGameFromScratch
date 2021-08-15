#pragma once

#include "Engine.h"
#include "Framework2D/Framework2DAPI.h"

#include "Framework2D/Structs/Vectors.h"

#include "GameMode.h"

namespace Framework2D {

	class LayerSystem;
	class Layer2D;
	class Layer2DDebug;
	class LayerGameplay;
	class LayerHUD;

	class FRAMEWORK2D_API Game2D : public Engine::Application
	{
		// Engine layers
		LayerSystem* SystemLayer;
		LayerHUD* HUDLayer;
		Layer2DDebug* DebugLayer;
		Layer2D* MainLayer;
		LayerGameplay* GameplayLayer;

		// powered by Unreal Engine underhood hehe)
		GameMode* CurrentGameMode = nullptr;

		// 2D Game Gameplay boundaries
		const Vec2 GameBoundLeft;
		const Vec2 GameBoundRight;

		// function for creating Game2D instance
		friend Game2D* CreateGame(const char* Title, unsigned int Width, unsigned int Height,
			const Vec2& GameBoundLeft, const Vec2& GameBoundRight);
		
		Game2D(const char* Title, unsigned int Width, unsigned int Height, 
			const Vec2& GameBoundLeft, const Vec2& GameBoundRight);

	public:
		void OnInitialize();
		inline ~Game2D();

		inline LayerSystem* GetSystemLayer() const { return SystemLayer; }
		inline LayerHUD* GetHUDLayer() const { return HUDLayer; }
		inline Layer2D* GetMainLayer() const { return MainLayer; }
		inline LayerGameplay* GetGameplayLayer() const { return GameplayLayer; }

		inline const Vec2& GetGameBoundLeft() const { return GameBoundLeft; }
		inline const Vec2& GetGameBoundRight() const { return GameBoundRight; }


		inline GameMode* GetCurrentGameMode() const { return CurrentGameMode; }
		inline void ChangeGameMode(GameMode* NewGameMode, bool bAutoStart = true);

		void DragDebugSolid(const Vec2& Position, const Vec2& Size, const Vec4& Color = Vec4::MagentaColor, float Time = 0.f);
		void DrawDebugBox(const Vec2& Position, const Vec2& Size, const Vec4& Color = Vec4::MagentaColor, float Time = 0.f);

		static Game2D* Instance;

	};

	// Scripting usefull functions

	inline Game2D* GetGame() { return Game2D::Instance; }
	
	inline GameMode* GetGM() { return Game2D::Instance ? Game2D::Instance->GetCurrentGameMode() : nullptr; }
	
	inline Level* GetLevel() { if (auto GM = GetGM()) return GM->GetLevel(); else return nullptr; }
	
	inline PlayerController* GetPlayerController() { if (auto GM = GetGM()) return GM->GetPlayerController(); else return nullptr; }
	
	inline HUD* GetHUD() { if (auto GM = GetGM()) return GM->GetHUD(); else return nullptr; }
	
	inline AIController* GetAIController() { if (auto GM = GetGM()) return GM->GetAIController(); else return nullptr; }

	//

	inline Game2D* CreateGame(const char* Title, unsigned int Width, unsigned int Height, 
		const Vec2& GameBoundLeft, const Vec2& GameBoundRight)
	{
		Game2D::Instance = new Game2D(Title, Width, Height, GameBoundLeft, GameBoundRight);
		return Game2D::Instance;
	}
}
