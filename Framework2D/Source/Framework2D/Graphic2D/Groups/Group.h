#pragma once

#include <Framework2D/Framework2DAPI.h>

#include "Engine.h"

namespace Framework2D {

	class BaseEntity;

	constexpr unsigned int GroupVecEntitiesReserve = 32;

	class FRAMEWORK2D_API Group
	{
		friend class BaseEntity;

	public:
		virtual ~Group() 
		{
			/*for (auto& Entity : Entities)
			{
				Entity->EntityGroup = nullptr;
				delete Entity;
			}*/
		}

		virtual void OnUpdate(float DeltaTime) =0;
		virtual void OnEvent(Engine::Event& e) =0;
		virtual void OnDraw()                  =0;

		inline std::string GetName() const { return GroupName; }

	protected:
		Group(const std::string& GroupName) : GroupName(GroupName)
		{
			Entities.reserve(GroupVecEntitiesReserve);
		}

		const std::string GroupName;

		std::vector<BaseEntity*> Entities;

		inline bool AddEntity(BaseEntity* Entity);
		inline bool RemoveEntity(BaseEntity* Entity);

		/** return first entity with matching name if exists */
		inline BaseEntity* FindEntity(const std::string& EntityName);

		/** true if exists at least on entity with matching name */
		inline bool HasEntity(const std::string& EntityName);
	};

}