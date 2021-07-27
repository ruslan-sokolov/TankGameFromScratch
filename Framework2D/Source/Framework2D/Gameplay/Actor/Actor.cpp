#include <PCH_Framework.h>
#include "Actor.h"

namespace Framework2D
{
	Actor::Actor(const std::string& Name, const VecInt2D& Position)
		: BaseEntity(Name, Position)
	{
	}

	Actor::~Actor()
	{

	}
}
