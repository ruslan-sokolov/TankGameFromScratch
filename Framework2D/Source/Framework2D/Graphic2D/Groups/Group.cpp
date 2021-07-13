#include "PCH_Framework.h"
#include "Group.h"

#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

	bool Group::AddEntity(BaseEntity* Entity)
	{
		if (Entity->HasGroup()) return false;

		if (Entities.size() >= GroupVecEntitiesReserve)
			Entities.resize(Entities.size() + GroupVecEntitiesReserve);

		Entity->EntityGroup = this;
		Entities.push_back(Entity);

		return true;
	}

	bool Group::RemoveEntity(BaseEntity* Entity)
	{
		auto Removed = std::remove(Entities.begin(), Entities.end(), Entity);
		if (Removed != Entities.end())
		{
			BaseEntity* Entity = *Removed;
			Entity->EntityGroup = nullptr;
			delete Entity;

			Entities.erase(Removed, Entities.end());
			return true;
		}
		return false;
	}

	BaseEntity* Group::FindEntity(const std::string& EntityName)
	{
		auto It = std::find_if(Entities.begin(), Entities.end(), [&](BaseEntity* e) {return e->Name == EntityName; });
		if (It != Entities.end()) return *It;

		return nullptr;
	}

	bool Group::HasEntity(const std::string& EntityName)
	{
		return FindEntity(EntityName) != nullptr;
	}

}