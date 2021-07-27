#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Engine.h>

namespace Framework2D {

	class Level;

	class FRAMEWORK2D_API LayerGameLevel : public Engine::Layer
	{
		Level* CurrentLevel = nullptr;

	public:
		LayerGameLevel(const std::string& LayerName);
		~LayerGameLevel();

		void OnUpdate(float DeltaTime) override;

		void SetLevel(Level* InLevel) { CurrentLevel = InLevel; }
		Level* GetLevel() const { return CurrentLevel; }
	};

}
