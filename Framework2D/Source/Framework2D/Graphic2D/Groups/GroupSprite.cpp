#include <PCH_Framework.h>
#include "GroupSprite.h"

#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>

namespace Framework2D {

	GroupSprite::GroupSprite(const std::string& GroupName): Group(GroupName) {}

	GroupSprite::~GroupSprite() {}

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
		renderer.ResetVertexQuads(Entities.size());

		SpriteEntity* Sprite;
		for (auto& Entity : Entities)
		{
			if (!Entity->IsRenderEnabled())  // check if should render
				continue;

			// fill renderer draw data
			Sprite = static_cast<SpriteEntity*>(Entity);
			renderer.CreateAndPushVertexQuad(Sprite->GetPosition(), Sprite->GetSize(), Sprite->GetColor(), (float)Sprite->texture->GetActiveSlot());
		}

		renderer.Draw();
	}

	inline bool GroupSprite::AddSprite(SpriteEntity* spriteEntity)
	{
		return Group::AddEntity(spriteEntity);
	}

	inline bool GroupSprite::RemoveSprite(SpriteEntity* spriteEntity)
	{
		return Group::RemoveEntity(spriteEntity);
	}

	inline SpriteEntity* GroupSprite::GetSprite(const std::string& SpriteName)
	{
		return static_cast<SpriteEntity*>(Group::FindEntity(SpriteName));
	}

	inline bool GroupSprite::HasSprite(const std::string& SpriteName)
	{
		return GetSprite(SpriteName) != nullptr;
	}
}