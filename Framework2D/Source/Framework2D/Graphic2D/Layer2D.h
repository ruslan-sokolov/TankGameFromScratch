#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Engine.h>

#include <map>

namespace Framework2D {

	class Group;

	class FRAMEWORK2D_API Layer2D : public Engine::Layer
	{
		std::map<std::string, Group*> Groups;

	public:
		Layer2D(const std::string& LayerName);
		~Layer2D();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e);

		bool AddGroup(Group* group);
		bool AddGroupFront(Group* group);
		bool AddGroupAfter(Group* GroupAdd, Group* GroupAfter);
		bool AddGroupBefore(Group* GroupAdd, Group* GroupBefore);
		bool SwapGroup(Group* GroupLeft, Group* GroupRight);
		
		bool RemoveGroup(Group* Group);
		bool IsGroupExists(Group* Group) const;
		bool IsGroupExists(const std::string& GroupName) const;
		Group* GetGroup(std::string GroupName);
		
	};

}