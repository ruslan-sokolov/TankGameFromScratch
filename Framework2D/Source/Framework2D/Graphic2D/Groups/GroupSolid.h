#pragma once

#include "Group.h"

#include "glm/glm.hpp"

namespace Framework2D {

	class SolidEntity;

	class FRAMEWORK2D_API GroupSolid : public Group
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
		GroupSolid(const std::string& GroupName);

		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;
		void OnDraw() override;

		bool AddSolid(SolidEntity* Solid);
		bool RemoveSolid(SolidEntity* Solid);
		SolidEntity* GetSolid(const std::string& SolidName);
		bool HasSolid(const std::string& SolidName);
	};

}


