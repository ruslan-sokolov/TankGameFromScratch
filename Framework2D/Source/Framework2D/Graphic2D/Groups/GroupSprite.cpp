#include "PCH_Framework.h"
#include "GroupSprite.h"
#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>

namespace Framework2D {

	GroupSprite::GroupSprite(const std::string& GroupName)
		: Group(GroupName)
	{

	}

	void GroupSprite::OnUpdate(float DeltaTime)
	{
		for (auto& Sprite : Entities)
		{
			Sprite->OnUpdate(DeltaTime);
		}
	}

	void GroupSprite::OnEvent(Engine::Event& e)
	{
		for (auto it = Entities.end(); it != Entities.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}

	void GroupSprite::OnDraw()
	{

	}

	bool GroupSprite::AddSprite(SpriteEntity* spriteEntity)
	{
		return Group::AddEntity(spriteEntity);
	}

	bool GroupSprite::RemoveSprite(SpriteEntity* spriteEntity)
	{
		return Group::RemoveEntity(spriteEntity);
	}

	SpriteEntity* GroupSprite::GetSprite(const std::string& SpriteName)
	{
		return static_cast<SpriteEntity*>(Group::FindEntity(SpriteName));
	}

	bool GroupSprite::HasSprite(const std::string& SpriteName)
	{
		return GetSprite(SpriteName) != nullptr;
	}
}