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
		void OnEvent(Engine::Event& e) override;

		inline bool AddGroup(Group* group);
		inline bool AddGroupFront(Group* group);
		inline bool AddGroupAfter(Group* GroupAdd, Group* GroupAfter);
		inline bool AddGroupBefore(Group* GroupAdd, Group* GroupBefore);
		inline bool SwapGroup(Group* GroupLeft, Group* GroupRight);
		
		inline bool RemoveGroup(Group* Group);
		inline bool IsGroupExists(Group* Group) const;
		inline bool IsGroupExists(const std::string& GroupName) const;
		inline Group* GetGroup(std::string GroupName);
		
	};

}