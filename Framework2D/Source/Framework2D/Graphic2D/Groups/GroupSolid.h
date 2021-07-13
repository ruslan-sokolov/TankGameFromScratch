#pragma once

#include "Group.h"

namespace Framework2D {

	class SolidEntity;

	class FRAMEWORK2D_API GroupSolid : public Group
	{
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


