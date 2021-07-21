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
		
		// Create texture buckets
		std::unordered_map<Texture*, std::vector<SpriteEntity*>> TextureBuckets;

		SpriteEntity* Sprite;
		for (auto& Entity: Entities)
		{
			if (!Entity->IsRenderEnabled())  // check if should render
				continue;

			Sprite = static_cast<SpriteEntity*>(Entity);

			auto& EntityBucket = TextureBuckets[Sprite->GetTexture()];
			EntityBucket.push_back(Sprite);
		}  //
		
		auto It_Begin = TextureBuckets.begin();
		auto It_End = TextureBuckets.begin();
		const int TexSlotsMax = Texture::GetMaxTextureBind();
		int TextureNumToDraw = TextureBuckets.size();
		while (TextureNumToDraw > 0)  
		{
			It_Begin = It_End;
			std::advance(It_End, TextureNumToDraw < TexSlotsMax ? TextureNumToDraw : TexSlotsMax);
			TextureNumToDraw -= TexSlotsMax;

			renderer.ResetVertexQuads(Entities.size());  // todo: fix unnecessary space allocation
			
			for (auto It = It_Begin; It != It_End; ++It)
			{
				Texture& texture = *(*It).first;
				texture.Bind();

				for (auto& Sprite : (*It).second)
				{
					renderer.CreateAndPushVertexQuad(Sprite->GetPosition(), Sprite->GetSize(), Sprite->GetColor(), (float)texture.GetActiveSlot());
				}
			}

			renderer.Draw();  // make few draw calls depends on max binded texture slots
		}
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