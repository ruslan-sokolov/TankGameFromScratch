#pragma once

#include "Group.h"

namespace Framework2D {

	class SpriteEntity;

	class FRAMEWORK2D_API GroupSprite : public Group
	{
	public:
		GroupSprite(const std::string& GroupName);

		void OnUpdate() override;
		void OnEvent(Engine::Event& e) override;

		bool AddSprite(SpriteEntity*);
		bool RemoveSprite(SpriteEntity*);
	};

}