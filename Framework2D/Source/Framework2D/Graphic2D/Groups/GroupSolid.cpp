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
			Solid->OnUpdate(DeltaTime);
		}
	}

	void GroupSolid::OnEvent(Engine::Event& e)
	{
		for (auto it = Entities.end(); it != Entities.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}

	void GroupSolid::OnDraw()
	{
		renderer.ResetVertexQuads(Entities.size());

		SolidEntity* Solid;
		for (auto& Entity : Entities)
		{
			// check if should render
			if (!Entity->IsRenderEnabled())
				continue;

			// fill vertex buffer data
			Solid = static_cast<SolidEntity*>(Entity);
			renderer.PushVertexQuad(std::move(Solid->GetVertexQuad()));
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