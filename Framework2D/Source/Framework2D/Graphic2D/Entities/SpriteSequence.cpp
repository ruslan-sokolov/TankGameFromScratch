#include <PCH_Framework.h>
#include "SpriteSequence.h"

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>
#include <Framework2D/Systems/SystemTimer.h>

namespace Framework2D {

	SpriteSequence::SpriteSequence(const std::string& Name, std::vector<Texture*>&& Textures, const Vec2& Position,
		float AnimRate, bool bAnimEnable, 
		const Vec2& Size, const Vec4& Color, bool bEnableRender)
		: SpriteEntity(Name, Textures[0], Position, Size, Color, bEnableRender), Textures(std::move(Textures)),
		CurrentTextureIndex(0), bAnimEnabled(bAnimEnable), AnimRate(AnimRate)
	{
		SetAnimEnable(bAnimEnable);
	}

	SpriteSequence::SpriteSequence(const std::string& Name, const std::initializer_list<const char*>& TexturePathList, const Vec2& Position, 
		float AnimRate, bool bAnimEnable, 
		const Vec2& Size, const Vec4& Color, bool bEnableRender)
		: SpriteSequence(Name, ResourceLoader::GetTextures(TexturePathList), Position, AnimRate, bAnimEnable, Size, Color, bEnableRender)
	{
	}

	SpriteSequence::~SpriteSequence()
	{
		SystemTimer::RemoveTimer(TimerHandle_SetNextTexture);
	}

	// timer callback
	inline void SpriteSequence::SetNextTexture_OnTimer()
	{
		SetNextFrame();
	}

	inline void SpriteSequence::SetAnimEnable(bool bEnable)
	{
		if (bEnable)
			SystemTimer::SetTimer(TimerHandle_SetNextTexture, TIMER_CALLBACK(SpriteSequence::SetNextTexture_OnTimer), AnimRate, true);
		else
			SystemTimer::RemoveTimer(TimerHandle_SetNextTexture);
	}

	inline void SpriteSequence::SetAnimRate(float NewAnimRate)
	{
		AnimRate = NewAnimRate;
		SetAnimEnable(true);
	}

	inline void SpriteSequence::SetNextFrame()
	{
		if (++CurrentTextureIndex == Textures.size()) CurrentTextureIndex = 0; // incr
		
		texture = Textures[CurrentTextureIndex]; // set new texture
		Size = { texture->GetWidth(), texture->GetHeight() };  // update size, todo: make var bCanChangeSize
	}

	inline void SpriteSequence::SetFrame(unsigned int Index)
	{
		if (Index >= Textures.size()) Index = Textures.size() - 1; // range check

		CurrentTextureIndex = Index; // set new index
		texture = Textures[Index];   // set new texture
	}
}
