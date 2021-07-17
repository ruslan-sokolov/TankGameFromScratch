#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Engine.h>

#include <vector>

namespace Framework2D {

	class Group;

	class FRAMEWORK2D_API Layer2D : public Engine::Layer
	{
		std::vector<Group*> Groups;

	public:
		Layer2D(const std::string& LayerName);
		~Layer2D();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;

		inline void AddGroup(Group* group);
		inline void AddGroupFront(Group* group);
		inline void AddGroupAfter(Group* GroupAdd, Group* GroupAfter);
		inline void AddGroupBefore(Group* GroupAdd, Group* GroupBefore);
		inline void SwapGroup(Group* GroupLeft, Group* GroupRight);
		
		inline void RemoveGroup(Group* group);
		
		inline bool IsGroupExists(Group* group);
		inline bool IsGroupExists(const std::string& GroupName);
		
		inline Group* GetGroup(const std::string& GroupName);
	};

}