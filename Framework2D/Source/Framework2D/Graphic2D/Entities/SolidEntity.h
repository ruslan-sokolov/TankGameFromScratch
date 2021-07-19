#pragma once

#include "BaseEntity.h"

namespace Framework2D {

	class GroupSolid;

	class FRAMEWORK2D_API SolidEntity : public BaseEntity
	{
		friend class GroupSolid;

		Vec4 Color;
		inline struct VertexBatchColorQuad GetVertexQuad();  // get data for renderer to use in group onDraw()

	public:
		SolidEntity(const std::string& Name, const Vec4& Color, const VecInt2D& Position, const VecInt2D& Size, bool bEnableRender=true);
		~SolidEntity();

		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;

		inline void SetColor(Vec4& Color) { this->Color = Color; }
		inline Vec4 GetColor() const { return Color; }
	};

}