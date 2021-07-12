#include "PCH_Framework.h"
#include "GroupSprite.h"
#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>

namespace Framework2D {

	GroupSprite::GroupSprite(const std::string& GroupName)
		: Group(GroupName)
	{

	}

	void GroupSprite::OnUpdate()
	{

	}

	void GroupSprite::OnEvent(Engine::Event& e)
	{

	}

	bool GroupSprite::AddSprite(SpriteEntity*)
	{
		return false;
	}

	bool GroupSprite::RemoveSprite(SpriteEntity*)
	{
		return false;
	}
}