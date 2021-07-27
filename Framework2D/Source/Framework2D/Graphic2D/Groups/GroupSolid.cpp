#include <PCH_Framework.h>
#include "GroupSolid.h"

#include <Framework2D/Graphic2D/Entities/SolidEntity.h>

namespace Framework2D {
	GroupSolid::GroupSolid(const std::string& GroupName): Group(GroupName) {}

	GroupSolid::~GroupSolid() {}

	void GroupSolid::OnUpdate(float DeltaTime)
	{
		for (auto& Solid : Entities)
		{
			Solid->OnTick(DeltaTime);
		}
	}

	void GroupSolid::OnDraw()
	{
		renderer.ResetVertexQuads(Entities.size());

		SolidEntity* Solid;
		for (auto& Entity : Entities)
		{
			if (!Entity->IsRenderEnabled())  // check if should render
				continue;

			// fill renderer draw data
			Solid = static_cast<SolidEntity*>(Entity);
			renderer.CreateAndPushVertexQuad(Solid->GetPosition(), Solid->GetSize(), Solid->GetColor());
		}
		
		renderer.Draw();
	}

	inline bool GroupSolid::AddSolid(SolidEntity* Solid)
	{
		return Group::AddEntity(Solid);
	}

	inline bool GroupSolid::RemoveSolid(SolidEntity* Solid)
	{
		return Group::RemoveEntity(Solid);
	}

	inline SolidEntity* GroupSolid::GetSolid(const std::string& SolidName)
	{
		return static_cast<SolidEntity*>(Group::FindEntity(SolidName));
	}

	inline bool GroupSolid::HasSolid(const std::string& SolidName)
	{
		return Group::FindEntity(SolidName) != nullptr;
	}
}
