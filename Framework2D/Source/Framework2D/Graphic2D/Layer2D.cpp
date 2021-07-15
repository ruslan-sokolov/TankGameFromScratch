#include <PCH_Framework.h>
#include "Layer2D.h"

#include "Groups/Group.h"
#include "Entities/BaseEntity.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
		// debug
		static float r_color = 0.0f;

		// debug test glfw call
		glClearColor(r_color, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		r_color += 1.0f * DeltaTime;
		if (r_color >= 1.0f) r_color = 0.0f;

		glm::vec3 SomeVec = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		//

		for (auto& pair : Groups)
		{
			pair.second->OnUpdate(DeltaTime);
			pair.second->OnDraw();
		}
	}

	void Layer2D::OnEvent(Engine::Event& e)
	{
		// ENGINE_LOG(LOG_INFO, "Layer2D: Event {0}", e.ToString());

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

