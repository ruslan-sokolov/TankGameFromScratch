#pragma once

#include "Group.h"

namespace Framework2D {

	class SpriteEntity;

	class FRAMEWORK2D_API GroupSprite : public Group
	{
	public:
		GroupSprite(const std::string& GroupName);

		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;
		void OnDraw() override;

		bool AddSprite(SpriteEntity* Sprite);
		bool RemoveSprite(SpriteEntity* Sprite);
		SpriteEntity* GetSprite(const std::string& SpriteName);
		bool HasSprite(const std::string& SpriteName);
	};

}
