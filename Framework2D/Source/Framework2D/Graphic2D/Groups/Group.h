#pragma once

#include <Framework2D/Framework2DAPI.h>

#include "Engine.h"

namespace Framework2D {

	class BaseEntity;

	class FRAMEWORK2D_API Group
	{
	public:
		Group(const std::string& GroupName) : GroupName(GroupName) {}
		virtual ~Group() {}

		virtual void OnUpdate() =0;
		virtual void OnEvent(Engine::Event& e) =0;

		inline std::string GetName() const { return GroupName; }

	protected:
		const std::string GroupName;

		std::vector<BaseEntity*> Entities;
	};

}