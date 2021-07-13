#pragma once

#include <Framework2D/Framework2DAPI.h>
#include "Engine.h"

namespace Framework2D {

	class Group;

	class FRAMEWORK2D_API BaseEntity
	{
		friend class Group;
	
	protected:
		Group* EntityGroup;
		const std::string Name;

		BaseEntity(const std::string& Name) : Name(Name), EntityGroup(nullptr) {}
		virtual ~BaseEntity();

	public:
		inline Group* GetGroup() const { return EntityGroup; }
		inline bool HasGroup() const { return EntityGroup != nullptr; }
		inline std::string GetName() const { return Name; }

		virtual void OnUpdate(float DeltaTime) = 0;
		virtual void OnEvent(Engine::Event& e) = 0;
	};
}