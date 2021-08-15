#pragma once

#include "HUDElement.h"

#include <vector>
#include <unordered_map>

#include <Framework2D/Graphic2D/Render/Renderer.h>

namespace Framework2D {

	class Texture;

	/*
	 * Struct with texture and normalized U,V,UL,VL values
	 */
	struct CanvasIcon
	{
		Texture* m_Texture;

		float U, V, UL, VL;

		Vec2 Size;

		CanvasIcon()
			: m_Texture(nullptr),
			 U(0),
			 V(0),
			UL(0),
			VL(0)
		{}
	};

	struct CanvasItem
	{
		const CanvasIcon& Icon;

		Vec2 Position;
		Vec2 Scale;
		Vec4 Color;

		VertexBatchTextureQuad CreateVertexQuad()
		{
			float Width = Icon.Size.X * Scale.X;
			float Height = Icon.Size.Y * Scale.Y;

			VertexBatchTexture V_0{  Position,                                 Color, { Icon.U,  Icon.VL }, 0 };
			VertexBatchTexture V_1{ {Position.X + Width, Position.Y},          Color, { Icon.UL, Icon.VL }, 0 };
			VertexBatchTexture V_2{ {Position.X + Width, Position.Y + Height}, Color, { Icon.UL, Icon.V  }, 0 };
			VertexBatchTexture V_3{ {Position.X,         Position.Y + Height}, Color, { Icon.U,  Icon.V  }, 0 };

			VertexBatchTextureQuad Quad = { V_0, V_1, V_2, V_3 };

			return Quad;
		}

		CanvasItem(const CanvasIcon& Icon, const Vec2& Position, const Vec2& Scale, const Vec4& Color)
			: Icon(Icon), Position(Position), Scale(Scale), Color(Color)
		{
		}

	};

	class HUDCanvas : public HUDElement
	{
		Renderer<VertexBatchTextureQuad> m_Renderer;

		static inline unsigned int ItemsVecExtend = 16;
		std::unordered_map<Texture*, std::vector<CanvasItem>> ItemsDrawBuckets;

	public:
		HUDCanvas();
		~HUDCanvas();

		void DrawItems()
		{
			for (auto& Pair : ItemsDrawBuckets)
			{
				m_Renderer.ResetVertexQuads(Pair.second.size());

				Texture& texture = *(Pair.first);
				texture.Bind();

				for (auto& Item : Pair.second)
				{
					auto VertQuad = Item.CreateVertexQuad();
					m_Renderer.PushVertexQuad(std::move(VertQuad));
				}
				
				m_Renderer.Draw();
			}

			ItemsDrawBuckets.clear();
		}

		void DrawIcon(const CanvasIcon& Icon, const Vec2& Position, const Vec2& Scale = Vec2::VecOne, const Vec4& Color = Vec4::WhiteColor)
		{
			auto& DrawBucket = ItemsDrawBuckets[Icon.m_Texture];

			// extend vector
			if (DrawBucket.size() % ItemsVecExtend == 0) 
				DrawBucket.reserve(DrawBucket.size() + ItemsVecExtend);

			CanvasItem Item(Icon, Position, Scale, Color);

			DrawBucket.emplace_back(std::move(Item));
		}

		// put texture and absolute U,V,UL,VL to create struct with texture and normalized U,V,UL,VL
		static CanvasIcon MakeCanvasIcon(Texture* InTexture, float U, float V, float UL, float VL)
		{
			float TexWidth_Inverted =  1.f / InTexture->GetWidth();
			float TexHeight_Inverted = 1.f / InTexture->GetHeight();
			
			float TexWidth_Strip = (UL - U) * TexWidth_Inverted;
			float TexHeight_Strip = (VL - V) * TexHeight_Inverted;

			CanvasIcon OutIcon;

			OutIcon.m_Texture = InTexture;
			OutIcon.U  =  U * TexWidth_Inverted;
			OutIcon.V  =  V * TexHeight_Inverted;
			OutIcon.UL = UL * TexWidth_Inverted;
			OutIcon.VL = VL * TexHeight_Inverted;
			OutIcon.Size =  { TexWidth_Strip, TexHeight_Strip };

			return OutIcon;
		}

		static CanvasIcon MakeCanvasIcon(Texture* InTexture)
		{
			CanvasIcon OutIcon;

			OutIcon.m_Texture = InTexture;
			OutIcon.U  = 0.f;
			OutIcon.V  = 0.f;
			OutIcon.UL = 1.f;
			OutIcon.VL = 1.f;
			OutIcon.Size = { InTexture->GetWidth(), InTexture->GetHeight() };

			return OutIcon;
		}
	};

}
