#pragma once

#include "Group.h"

#include <Framework2D/Graphic2D/Render/Renderer.h>

namespace Framework2D {

	class SolidEntity;

	class FRAMEWORK2D_API GroupSolid : public Group
	{
		Renderer<VertexBatchColorQuad> renderer;

	public:
		GroupSolid(const std::string& GroupName);
		~GroupSolid();

		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;
		void OnDraw() override;

		inline bool AddSolid(SolidEntity* Solid);
		inline bool RemoveSolid(SolidEntity* Solid);
		inline SolidEntity* GetSolid(const std::string& SolidName);
		inline bool HasSolid(const std::string& SolidName);
	};

}


