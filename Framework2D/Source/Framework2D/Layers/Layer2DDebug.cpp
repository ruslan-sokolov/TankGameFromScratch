#include <PCH_Framework.h>
#include "Layer2DDebug.h"

#include <Framework2D/Graphic2D/Groups/GroupSolid.h>
#include <Framework2D/Graphic2D/Entities/SolidEntity.h>

#include <Framework2D/Systems/SystemTimer.h>

namespace Framework2D
{
	Layer2DDebug::Layer2DDebug(const std::string& LayerName)
		: Layer2D(LayerName), DebugSolidGroup(nullptr)
	{
	}

	Layer2DDebug::~Layer2DDebug()
	{
		if (DebugSolidGroup)
		{
			for (auto& Entity : *DebugSolidGroup)
			{
				delete Entity;
			}
		}
	}

	void Layer2DDebug::OnInitialize()
	{
		DebugSolidGroup = new GroupSolid("DebugSolidGroup");
		AddGroup(DebugSolidGroup);
	}

	void Layer2DDebug::DrawDebugSolid(const Vec2& Position, const Vec2& Size, const Vec4& Color, float Time)
	{
		ENGINE_ASSERT(DebugSolidGroup, "Layer2DDebug need initialization!!!");
		if (!DebugSolidGroup) return;

		auto Solid = new SolidEntity("DebugSolid", Color, Position - Size / 2, Size);
		DebugSolidGroup->AddSolid(Solid);

		if (Time != 0.f)
		{
			TimerHandle TimerHandle_Empty;
			SystemTimer::SetTimer(TimerHandle_Empty, [=]() { delete Solid; }, Time);
		}
	}

	void Layer2DDebug::DrawDebugBox(const Vec2& Position, const Vec2& Size, const Vec4& Color, float Time)
	{
		ENGINE_ASSERT(DebugSolidGroup, "Layer2DDebug need initialization!!!");
		if (!DebugSolidGroup) return;

		auto Top = new SolidEntity("DebugSolid", Color, Position, { Size.X, 1.0f });
		auto Bottom = new SolidEntity("DebugSolid", Color, {Position.X, Position.Y + Size.Y}, { Size.X, 1.0f });
		auto Left = new SolidEntity("DebugSolid", Color, Position, { 1.0f, Size.Y });
		auto Right = new SolidEntity("DebugSolid", Color, { Position.X + Size.X, Position.Y }, { 1.0f, Size.Y });
		
		DebugSolidGroup->AddSolid(Top);
		DebugSolidGroup->AddSolid(Bottom);
		DebugSolidGroup->AddSolid(Left);
		DebugSolidGroup->AddSolid(Right);

		if (Time != 0.f)
		{
			TimerHandle TimerHandle_Empty;
			SystemTimer::SetTimer(TimerHandle_Empty, [=]() { delete Top; delete Bottom; delete Left; delete Right; }, Time);
		}
	}
}