#pragma once

#include "Group.h"

namespace Framework2D {

	class SolidEntity;

	class FRAMEWORK2D_API GroupSolid : public Group
	{
	public:
		GroupSolid(const std::string& GroupName);

		void OnUpdate() override;
		void OnEvent(Engine::Event& e) override;

		bool AddSolid(SolidEntity*);
		bool RemoveSolid(SolidEntity*);
	};

}