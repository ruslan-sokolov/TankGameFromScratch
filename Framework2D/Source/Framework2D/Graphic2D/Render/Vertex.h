#pragma once

#include <Framework2D/Structs/Vectors.h>

namespace Framework2D {

	struct FRAMEWORK2D_API VertexBatchTexture
	{
		Vec2 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TextureSlot;
	};

	struct FRAMEWORK2D_API VertexBatchTextureQuad
	{
		VertexBatchTexture Vertices[4];
	};

	struct FRAMEWORK2D_API VertexBatchColor
	{
		Vec2 Position;
		Vec4 Color;
	};

	struct FRAMEWORK2D_API VertexBatchColorQuad
	{
		VertexBatchColor Vertices[4];
	};

}
