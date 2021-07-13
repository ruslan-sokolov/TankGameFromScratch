#include <PCH_Framework.h>
#include "Layer2D.h"

#include "Groups/Group.h"
#include "Entities/BaseEntity.h"

namespace Framework2D {

	Layer2D::Layer2D(const std::string& LayerName)
		: Layer(LayerName)
	{

	}

	Layer2D::~Layer2D()
	{
		Layer::~Layer();
	}

	void Layer2D::OnAttach()
	{

	}

	void Layer2D::OnDetach()
	{

	}

	void Layer2D::OnUpdate(float DeltaTime)
	{
		for (auto& pair : Groups)
		{
			pair.second->OnUpdate(DeltaTime);
			pair.second->OnDraw();
		}
	}

	void Layer2D::OnEvent(Engine::Event& e)
	{
		ENGINE_LOG(LOG_INFO, "Layer2D: Event {0}", e.ToString());

		for (auto& pair : Groups)
		{
			pair.second->OnEvent(e);
		}
	}

	bool Layer2D::AddGroup(Group* group)
	{
		Groups[group->GetName()] = group;

		return true;
	}

	bool Layer2D::AddGroupFront(Group* group)
	{

		return false;
	}

	bool Layer2D::AddGroupAfter(Group* GroupAdd, Group* GroupAfter)
	{
		return false;
	}

	bool Layer2D::AddGroupBefore(Group* GroupAdd, Group* GroupBefore)
	{
		return false;
	}

	bool Layer2D::SwapGroup(Group* GroupLeft, Group* GroupRight)
	{
		return false;
	}

	bool Layer2D::RemoveGroup(Group* Group)
	{
		return false;
	}

	bool Layer2D::IsGroupExists(Group* Group) const
	{
		return false;
	}

	bool Layer2D::IsGroupExists(const std::string& GroupName) const
	{
		return false;
	}

	Group* Layer2D::GetGroup(std::string GroupName)
	{
		return nullptr;
	}

}

