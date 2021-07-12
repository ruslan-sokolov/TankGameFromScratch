#include "PCH_Framework.h"
#include "GroupSolid.h"
#include <Framework2D/Graphic2D/Entities/SolidEntity.h>

namespace Framework2D {

	GroupSolid::GroupSolid(const std::string& GroupName)
		: Group(GroupName)
	{

	}

	void GroupSolid::OnUpdate()
	{

	}

	void GroupSolid::OnEvent(Engine::Event& e)
	{

	}

	bool GroupSolid::AddSolid(SolidEntity*)
	{
		return false;
	}

	bool GroupSolid::RemoveSolid(SolidEntity*)
	{
		return false;
	}

}