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
		: SpriteEntity(Name, ResourceLoader::GetTexture(TexturePath), Position, Size, Color, bEnableRender)
	{
	}

	SpriteEntity::~SpriteEntity()
	{

	}

	void SpriteEntity::OnTick(float DeltaTime)
	{
	}

	void SpriteEntity::OnCollide(BaseEntity* Other, CollisionFilter Filter)
	{
	}

}
