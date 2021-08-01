#pragma once

#include "BaseEntity.h"

namespace Framework2D {

	class GroupSolid;

	class FRAMEWORK2D_API SolidEntity : public BaseEntity
	{
		friend class GroupSolid;

		Vec4 Color;

	public:
		SolidEntity(const std::string& Name, const Vec4& Color, const Vec2& Position, const Vec2& Size, bool bEnableRender=true);
		~SolidEntity();

		void OnUpdate(float DeltaTime) override;
		void OnCollide(BaseEntity* Other, CollisionFilter Filter) override;

		inline void SetColor(Vec4& Color) { this->Color = Color; }
		inline Vec4 GetColor() const { return Color; }
	};

}
