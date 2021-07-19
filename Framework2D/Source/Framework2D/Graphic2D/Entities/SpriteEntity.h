#pragma once

#include "BaseEntity.h"

namespace Framework2D {

	class GroupSprite;
	class Texture;

	class FRAMEWORK2D_API SpriteEntity : public BaseEntity
	{
		friend class GroupSprite;

		Vec4 Color;
		Texture* texture;
		
		struct VertexBatchTextureQuad GetVertexQuad();  // get data for renderer to use in group onDraw()

	public:
		// Constructor with texture instance ptr
		SpriteEntity(const std::string& Name, Texture* texture,
			const VecInt2D& Position, const VecInt2D& Size = VecInt2D::VecZero, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);
		
		// Construct with texture resource location path
		SpriteEntity(const std::string& Name, const std::string& TexturePath,
			const VecInt2D& Position, const VecInt2D& Size = VecInt2D::VecZero, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);
		
		~SpriteEntity();

		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;

		inline void SetColor(const Vec4& Color) { this->Color = Color; }
		inline Vec4 GetColor() const { return Color; }
		inline void SetTexture(Texture* texture) { this->texture = texture; }
	};

}
