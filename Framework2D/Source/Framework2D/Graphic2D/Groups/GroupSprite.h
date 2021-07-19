#pragma once

#include "Group.h"

#include "glm/glm.hpp"

namespace Framework2D {

	class SpriteEntity;

	class FRAMEWORK2D_API GroupSprite : public Group
	{
		unsigned int QuadVA;
		unsigned int QuadVB;
		unsigned int QuadIB;

		static const glm::mat4 IdentityMatrix;

		static glm::mat4 Proj;
		static glm::mat4 View;
		
		static glm::vec3 Translation;

		class Shader* shader;

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
