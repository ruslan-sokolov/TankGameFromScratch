#include <PCH_Framework.h>
#include "SpriteFlipFlop.h"

#include <Framework2D/Systems/SystemTimer.h>
#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

namespace Framework2D
{
	SpriteFlipFlop::SpriteFlipFlop(const std::string& Name, Texture* TextureFlip, Texture* TextureFlop, const VecInt2D& Position, 
		float FlipFlopRate, bool bAutoFlipFlopEnabled,
		const VecInt2D& Size, const Vec4& Color, bool bEnableRender)
		: SpriteEntity(Name, TextureFlip, Position, Size, Color, bEnableRender), 
		TextureFlip(texture), TextureFlop(TextureFlop), 
		bCurrentIsFlip(true), bAutoFlipFlopEnabled(bAutoFlipFlopEnabled), FlipFlopRate(FlipFlopRate)
	{
		SetAutoFlipFlopEnable(bAutoFlipFlopEnabled);
	}

	SpriteFlipFlop::SpriteFlipFlop(const std::string& Name, const std::string& TextureFlipPath, const std::string& TextureFlopPath, const VecInt2D& Position,
		float FlipFlopRate, bool bAutoFlipFlopEnabled,
		const VecInt2D& Size, const Vec4& Color, bool bEnableRender)
		: SpriteFlipFlop(Name, ResourceLoader::GetTexture(TextureFlipPath), ResourceLoader::GetTexture(TextureFlopPath), Position,
			FlipFlopRate, bAutoFlipFlopEnabled, Size, Color, bEnableRender)
	{
	}

	SpriteFlipFlop::~SpriteFlipFlop()
	{
		TimerHandle_FlipFlop.Invalidate();
	}

	// timer callback
	inline void SpriteFlipFlop::FlipFlop_OnTimer()
	{
		SetFlipFlop(!bCurrentIsFlip);
	}

	inline void SpriteFlipFlop::SetAutoFlipFlopEnable(bool bEnable)
	{
		if (bEnable) 
			SystemTimer::SetTimer(TimerHandle_FlipFlop, TIMER_CALLBACK(SpriteFlipFlop::FlipFlop_OnTimer), FlipFlopRate, true);
		else
			SystemTimer::RemoveTimer(TimerHandle_FlipFlop);
	}

	inline void SpriteFlipFlop::SetFlipFlopRate(float NewTimePeriod)
	{
		FlipFlopRate = NewTimePeriod;
		SetAutoFlipFlopEnable(true);
	}

	inline void SpriteFlipFlop::SetFlipFlop(bool bNewIsFlip)
	{
		bCurrentIsFlip = bNewIsFlip;

		if (bNewIsFlip)
			texture = TextureFlip;
		else
			texture = TextureFlop;

		Size = { texture->GetWidth(), texture->GetHeight() };   // update size, todo: make var bCanChangeSize
	}

}
