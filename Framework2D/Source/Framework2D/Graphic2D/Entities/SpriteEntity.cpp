#include "PCH_Framework.h"
#include "SpriteEntity.h"

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

namespace Framework2D {

	SpriteEntity::SpriteEntity(const std::string& Name, Texture* texture, const VecInt2D& Position, 
		const VecInt2D& Size, const Vec4& Color, bool bEnableRender)
		: BaseEntity(Name, Size, Position, bEnableRender), texture(texture), Color(Color)
	{
		if (Size == VecInt2D::VecZero)
			this->Size = { texture->GetWidth(), texture->GetHeight() };
	}

	SpriteEntity::SpriteEntity(const std::string& Name, const std::string& TexturePath, const VecInt2D& Position, 
		const VecInt2D& Size, const Vec4& Color, bool bEnableRender)
		: BaseEntity(Name, Size, Position, bEnableRender), Color(Color)
	{
		texture = ResourceLoader::GetTexture(TexturePath);

		if (Size == VecInt2D::VecZero)
			this->Size = { texture->GetWidth(), texture->GetHeight() };
	}

	SpriteEntity::~SpriteEntity()
	{

	}

	void SpriteEntity::OnUpdate(float DeltaTime)
	{
	}

	void SpriteEntity::OnEvent(Engine::Event& e)
	{
	}

	inline VertexBatchTextureQuad SpriteEntity::GetVertexQuad()
	{
		float TextureSlot = static_cast<float>(texture->GetActiveSlot());
		VertexBatchTexture v0 = { Position, Color, {0, 0}, TextureSlot };
		VertexBatchTexture v1 = { {Position.X + Size.X, Position.Y}, Color, {1, 0}, TextureSlot };
		VertexBatchTexture v2 = { {Position.X + Size.X, Position.Y + Size.Y}, Color, {1, 1}, TextureSlot };
		VertexBatchTexture v3 = { {Position.X, Position.Y + Size.Y}, Color, {0, 1}, TextureSlot };

		return { v0, v1, v2, v3 };
	}

}