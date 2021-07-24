#pragma once

#include "Group.h"

#include <Framework2D/Graphic2D/Render/Renderer.h>

namespace Framework2D {

	class SpriteEntity;

	class FRAMEWORK2D_API GroupSprite : public Group
	{
		Renderer<VertexBatchTextureQuad> renderer;

	public:
		GroupSprite(const std::string& GroupName);
		~GroupSprite();

		void OnUpdate(float DeltaTime) override;
		void OnDraw() override;

		inline bool AddSprite(SpriteEntity* Sprite);
		inline bool RemoveSprite(SpriteEntity* Sprite);
		inline SpriteEntity* GetSprite(const std::string& SpriteName);
		inline bool HasSprite(const std::string& SpriteName);
	};

}
