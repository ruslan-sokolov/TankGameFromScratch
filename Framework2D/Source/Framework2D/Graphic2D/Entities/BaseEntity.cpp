#include <PCH_Framework.h>
#include "BaseEntity.h"

#include <Framework2D/Graphic2D/Groups/Group.h>

namespace Framework2D {

	BaseEntity::~BaseEntity()
	{
		if (EntityGroup != nullptr)
			EntityGroup->RemoveEntity(this);
	}

}