#pragma once

#include "SpriteEntity.h"

#include <Framework2D/Structs/TimerHandle.h>

namespace Framework2D {

	class FRAMEWORK2D_API SpriteFlipFlop : public SpriteEntity
	{
		Texture* TextureFlip;
		Texture* TextureFlop;

		/** If True - render TextureFlip */
		bool bCurrentIsFlip;
		/** Control auto FlipFlop, if True - Textures will swap on timer */
		bool bAutoFlipFlopEnabled;

		/** Texture change time */
		float FlipFlopRate;
		/** Texture swap timer handler */
		TimerHandle TimerHandle_FlipFlop;
		/** Timer callback to swap textures */
		inline void FlipFlop_OnTimer();

	public:
		// Create instance with texture
		SpriteFlipFlop(const std::string& Name, Texture* TextureFlip, Texture* TextureFlop, const Vec2Int& Position,
			float FlipFlopRate = 0, bool bAutoFlipFlopEnabled = true,
			const Vec2Int& Size = 0, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);

		// Create instance with texturePath
		SpriteFlipFlop(const std::string& Name, const std::string& TextureFlipPath, const std::string& TextureFlopPath, const Vec2Int& Position,
			float FlipFlopRate = 0, bool bAutoFlipFlopEnabled = true,
			const Vec2Int& Size = 0, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);

		~SpriteFlipFlop();

		inline void SetAutoFlipFlopEnable(bool bEnable);
		inline bool IsAutoFlipFlopEnabled() const { return bAutoFlipFlopEnabled; }

		inline void SetFlipFlopRate(float NewTimePeriod);
		inline float GetFlipFlopRate() const { return FlipFlopRate; }

		/** Manual controlled flip flop */
		inline void SetFlipFlop(bool bNewIsFlip);
		inline bool IsCurrentFlip() const { return bCurrentIsFlip; }
	};

}
