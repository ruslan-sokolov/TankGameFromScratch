#include <PCH_Framework.h>
#include "Layer2D.h"

#include <Framework2D/Graphic2D/Groups/Group.h>
#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

	Layer2D::Layer2D(const std::string& LayerName)
		: Layer(LayerName)
	{
	}

	Layer2D::~Layer2D()
	{
		for (auto g : Groups) delete g;
	}

	void Layer2D::OnUpdate(float DeltaTime)
	{
		for (auto& g : Groups)
		{
			g->OnUpdate(DeltaTime);
			g->OnDraw();
		}
	}

	inline void Layer2D::AddGroup(Group* group)
	{
		Groups.push_back(group);
	}

	inline void Layer2D::AddGroupFront(Group* group)
	{
		Groups.emplace(Groups.begin(), group);
	}

	inline void Layer2D::AddGroupAfter(Group* GroupAdd, Group* GroupAfter)
	{
		auto It = std::find(Groups.begin(), Groups.end(), GroupAfter);
		
		if (It != Groups.end()) Groups.emplace(++It, GroupAdd);
	}

	inline void Layer2D::AddGroupBefore(Group* GroupAdd, Group* GroupBefore)
	{
		auto It = std::find(Groups.begin(), Groups.end(), GroupBefore);
		if (It != Groups.end()) Groups.emplace(It, GroupAdd);
	}

	inline void Layer2D::SwapGroup(Group* GroupLeft, Group* GroupRight)
	{
		auto ItLeft = std::find(Groups.begin(), Groups.end(), GroupLeft);
		auto ItRight = std::find(Groups.begin(), Groups.end(), GroupRight);

		if (ItLeft != Groups.end() && ItRight != Groups.end())
		{
			std::iter_swap(ItLeft, ItRight);
		}
	}

	inline void Layer2D::RemoveGroup(Group* group)
	{
		auto It = std::find(Groups.begin(), Groups.end(), group);
		if (It != Groups.end())
		{
			Groups.erase(It);
		}
	}

	inline bool Layer2D::IsGroupExists(Group* group)
	{
		return std::find(Groups.begin(), Groups.end(), group) != Groups.end();
	}

	inline bool Layer2D::IsGroupExists(const std::string& GroupName)
	{
		return GetGroup(GroupName) != nullptr;
	}
	
	Group* Layer2D::GetGroup(const std::string& GroupName)
	{
		auto Lambda = [&](Group* g) { return g->GetName() == GroupName; };
		auto It = std::find_if(Groups.begin(), Groups.end(), Lambda);

		if (It != Groups.end()) return *It;
		else return nullptr;
	}

}
