#pragma once

#include "Layer2D.h"

#include <Framework2D/Structs/Vectors.h>


namespace Framework2D
{
	class Layer2DDebug : public Layer2D
	{
		class GroupSolid* DebugSolidGroup;

	public:

		Layer2DDebug(const std::string& LayerName);
		~Layer2DDebug();

		void OnInitialize();

		void DrawDebugSolid(const Vec2& Position, const Vec2& Size, const Vec4& Color = Vec4::MagentaColor, float Time = 0.f);
		void DrawDebugBox(const Vec2& Position, const Vec2& Size, const Vec4& Color = Vec4::MagentaColor, float Time = 0.f);
	};
}