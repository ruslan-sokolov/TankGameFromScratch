#pragma once

#include "SpriteEntity.h"

#include <Framework2D/Structs/TimerHandle.h>
#include <initializer_list>

namespace Framework2D {

	class FRAMEWORK2D_API SpriteSequence : public SpriteEntity
	{
		std::vector<Texture*> Textures;

		/** Current Texture index from vector Textures */
		int CurrentTextureIndex;
		/** Control animation enable/disable state */
		bool bAnimEnabled;

		/** Texture change time */
		float AnimRate;
		/** Texture change timer handler */
		TimerHandle TimerHandle_SetNextTexture;
		/** Timer callback to set next texture */
		inline void SetNextTexture_OnTimer();

	public:
		SpriteSequence(const std::string& Name, std::vector<Texture*>&& Textures, const VecInt2D& Position,
			float AnimRate = 0, bool bAnimEnable = true, 
			const VecInt2D& Size = 0, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);

		SpriteSequence(const std::string& Name, const std::initializer_list<const char*>& TexturePathList, const VecInt2D& Position,
			float AnimRate = 0, bool bAnimEnable = true,
			const VecInt2D& Size = 0, const Vec4& Color = Vec4::WhiteColor, bool bEnableRender = true);

		~SpriteSequence();

		inline void SetAnimEnable(bool bEnable);
		inline bool IsAnimEnabled() const { return bAnimEnabled; }

		inline void SetAnimRate(float NewAnimRate);
		inline float GetAnimRate() const { return AnimRate; }

		/** manual controlled texture change */
		inline void SetNextFrame();
		inline void SetFrame(unsigned int Index);
		inline int GetCurrentIndex() const { return CurrentTextureIndex; }

	};

}