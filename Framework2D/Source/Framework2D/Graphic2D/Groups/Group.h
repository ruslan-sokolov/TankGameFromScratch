#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	class BaseEntity;
	class Layer2D;

	constexpr unsigned int GroupVecEntitiesReserve = 32;

	class FRAMEWORK2D_API Group
	{
		friend BaseEntity;
		friend Layer2D;

		Layer2D* Layer = nullptr;

	public:
		virtual ~Group();

		virtual void OnUpdate(float DeltaTime) =0;
		virtual void OnDraw()                  =0;

		inline std::string GetName() const { return GroupName; }

	protected:
		inline Group(const std::string& GroupName) : GroupName(GroupName) {}

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
