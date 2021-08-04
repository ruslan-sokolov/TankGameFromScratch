#include "PCH_Framework.h"
#include "Group.h"

#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

	Group::~Group()
	{
	}

	inline bool Group::AddEntity(BaseEntity* Entity)
	{
		if (Entity->HasGroup()) return false;

		if (Entities.size() % GroupVecEntitiesReserve == 0)
		{
			Entities.reserve(Entities.size() + GroupVecEntitiesReserve);
		}

		Entity->EntityGroup = this;
		Entities.push_back(Entity);

		return true;
	}
	
	inline bool Group::RemoveEntity(BaseEntity* EntityToRemove)
	{
		auto It = std::find(Entities.begin(), Entities.end(), EntityToRemove);
		if (It != Entities.end())
		{
			BaseEntity* Entity = *It;
			Entity->EntityGroup = nullptr;
			
			Entities.erase(It);
			return true;
		}
		return false;
	}

	inline BaseEntity* Group::FindEntity(const std::string& EntityName)
	{
		auto It = std::find_if(Entities.begin(), Entities.end(), [&](BaseEntity* e) {return e->Name == EntityName; });
		if (It != Entities.end()) return *It;

		return nullptr;
	}

	inline bool Group::HasEntity(const std::string& EntityName)
	{
		return FindEntity(EntityName) != nullptr;
	}

}
