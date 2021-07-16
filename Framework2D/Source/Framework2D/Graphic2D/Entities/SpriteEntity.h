#pragma once

#include "BaseEntity.h"

namespace Framework2D {

	class GroupSprite;
	class Texture;

	struct VertexBatchTexture
	{
		Vec2 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TextureSlot;
	};

	struct VertexBatchTextureQuad
	{
		VertexBatchTexture Vertices[4];
	};

	class FRAMEWORK2D_API SpriteEntity : public BaseEntity
	{
		friend class GroupSprite;

		Vec4 Color;
		Texture* texture;

		VertexBatchTextureQuad GetVertexQuad();

	public:
		// Constructor with texture ptr assignement 
		SpriteEntity(const std::string& Name, Texture* texture,
			const VecInt2D& Position, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);
		SpriteEntity(const std::string& Name, const std::string& TexturePath,
			const VecInt2D& Position, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);
		
		~SpriteEntity();

		inline void SetColor(const Vec4& Color) { this->Color = Color; }
		inline Vec4 GetColor() const { return Color; }
		inline void SetTexture(Texture* texture) { this->texture = texture; }
	};

}
