#include "PCH_Framework.h"
#include "SpriteEntity.h"

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

namespace Framework2D {

	SpriteEntity::SpriteEntity(const std::string& Name, Texture* texture, const VecInt2D& Position, 
		const Vec4& Color, bool bEnableRender)
		: BaseEntity(Name, { 0, 0 }, Position, bEnableRender), texture(texture), Color(Color)
	{
		Size = { texture->GetWidth(), texture->GetHeight() };
	}

	SpriteEntity::SpriteEntity(const std::string& Name, const std::string& TexturePath, const VecInt2D& Position, 
		const Vec4& Color, bool bEnableRender)
		: BaseEntity(Name, { 0, 0 }, Position, bEnableRender), Color(Color)
	{
		texture = ResourceLoader::GetTexture(TexturePath);
		Size = { texture->GetWidth(), texture->GetHeight() };
	}

	SpriteEntity::~SpriteEntity()
	{

	}

	VertexBatchTextureQuad SpriteEntity::GetVertexQuad()
	{
		int TextureSlot = texture->GetActiveSlot();
		VertexBatchTexture v0 = { Position, Color, {0, 0}, TextureSlot};
		VertexBatchTexture v1 = { {Position.X + Size.X, Position.Y}, Color, {0, 0}, TextureSlot };
		VertexBatchTexture v2 = { {Position.X + Size.X, Position.Y + Size.Y}, Color, {0, 0}, TextureSlot };
		VertexBatchTexture v3 = { {Position.X, Position.Y + Size.Y}, Color, {0, 0}, TextureSlot };

		return { v0, v1, v2, v3 };
	}

}