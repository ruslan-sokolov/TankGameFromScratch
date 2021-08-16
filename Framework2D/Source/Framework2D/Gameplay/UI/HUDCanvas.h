#pragma once

#include "HUDElement.h"

#include <Framework2D/Graphic2D/Render/Renderer.h>

namespace Framework2D {

	/*
	 * Struct with texture and normalized U,V,UL,VL values
	 * Can be reused
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
			VL(0) {}
	};

	/*
	 * Actual HUD Icon that generates vertex quads and can be drawed at canvas frame per frame
	 */
	struct CanvasItem
	{
		const CanvasIcon& Icon;

		Vec2 Position;
		Vec2 Scale;
		Vec4 Color;

		inline VertexBatchTextureQuad CreateVertexQuad(uint32_t ActiveTexSlot);

		CanvasItem(const CanvasIcon& Icon, const Vec2& Position, const Vec2& Scale, const Vec4& Color)
			: Icon(Icon), Position(Position), Scale(Scale), Color(Color) {}

	};

	/*
	 * Class that represents view for hud if it's mvc paradigm
	 */
	class HUDCanvas : public HUDElement
	{
		Renderer<VertexBatchTextureQuad> m_Renderer;

		static inline unsigned int ItemsVecExtend = 16;
		std::unordered_map<Texture*, std::vector<CanvasItem>> ItemsDrawBuckets;

	public:
		HUDCanvas();
		~HUDCanvas();

		// actual function with draw logic, this is where gpu draw calls happend
		inline void DrawItems();

		// should be called in HUD::DrawHUD(float), this one is for drawing icons per frame
		inline void DrawIcon(const CanvasIcon& Icon, const Vec2& Position, const Vec2& Scale = Vec2::VecOne, const Vec4& Color = Vec4::WhiteColor);

		// put texture and absolute U,V,UL,VL to create struct with texture and normalized U,V,UL,VL and striped tex size
		static inline CanvasIcon MakeCanvasIcon(Texture* InTexture, float U, float V, float UL, float VL);

		// put texture and absolute U,V,UL,VL to create struct with texture and normalized U,V,UL,VL and striped tex size
		static inline CanvasIcon MakeCanvasIcon(const std::string& InTexPath, float U, float V, float UL, float VL)
		{
			return MakeCanvasIcon(ResourceLoader::GetTexture(InTexPath), U, V, UL, VL);
		}

		// create canvas icon from texture with default UV
		static inline CanvasIcon MakeCanvasIcon(Texture* InTexture);

		// create canvas icon from texture with default UV
		static CanvasIcon MakeCanvasIcon(const std::string& InTexPath)
		{
			return MakeCanvasIcon(ResourceLoader::GetTexture(InTexPath));
		}
	};


	inline VertexBatchTextureQuad CanvasItem::CreateVertexQuad(uint32_t ActiveTexSlot)
	{
		float Width = Icon.Size.X * Scale.X;
		float Height = Icon.Size.Y * Scale.Y;

		VertexBatchTexture V_0{  Position,                                 Color, { Icon.U,  Icon.VL }, ActiveTexSlot };
		VertexBatchTexture V_1{ {Position.X + Width, Position.Y},          Color, { Icon.UL, Icon.VL }, ActiveTexSlot };
		VertexBatchTexture V_2{ {Position.X + Width, Position.Y + Height}, Color, { Icon.UL, Icon.V  }, ActiveTexSlot };
		VertexBatchTexture V_3{ {Position.X,         Position.Y + Height}, Color, { Icon.U,  Icon.V  }, ActiveTexSlot };

		VertexBatchTextureQuad Quad = { V_0, V_1, V_2, V_3 };

		return Quad;

	}


	inline void HUDCanvas::DrawItems()
	{
		for (auto& Pair : ItemsDrawBuckets)
		{
			m_Renderer.ResetVertexQuads(Pair.second.size());
			
			Texture& texture = *(Pair.first);
			texture.Bind();

			for (auto& Item : Pair.second)
			{
				auto VertQuad = Item.CreateVertexQuad(texture.GetActiveSlot());
				m_Renderer.PushVertexQuad(std::move(VertQuad));
			}

			m_Renderer.Draw();
		}

		ItemsDrawBuckets.clear();

	}


	inline void HUDCanvas::DrawIcon(const CanvasIcon& Icon, const Vec2& Position, const Vec2& Scale, const Vec4& Color)
	{
		auto& DrawBucket = ItemsDrawBuckets[Icon.m_Texture];

		// extend vector
		if (DrawBucket.size() % ItemsVecExtend == 0)
			DrawBucket.reserve(DrawBucket.size() + ItemsVecExtend);

		CanvasItem Item(Icon, Position, Scale, Color);

		DrawBucket.emplace_back(std::move(Item));

	}

	inline CanvasIcon HUDCanvas::MakeCanvasIcon(Texture* InTexture, float U, float V, float UL, float VL)
	{
		float TexWidth_Inverted = 1.f / InTexture->GetWidth();
		float TexHeight_Inverted = 1.f / InTexture->GetHeight();

		float TexWidth_Strip = UL - U;
		float TexHeight_Strip = VL - V;

		CanvasIcon OutIcon;

		OutIcon.m_Texture = InTexture;
		OutIcon.U = U * TexWidth_Inverted;
		OutIcon.V = V * TexHeight_Inverted;
		OutIcon.UL = UL * TexWidth_Inverted;
		OutIcon.VL = VL * TexHeight_Inverted;
		OutIcon.Size = { TexWidth_Strip, TexHeight_Strip };

		return OutIcon;

	}

	inline CanvasIcon HUDCanvas::MakeCanvasIcon(Texture* InTexture)
	{
		CanvasIcon OutIcon;

		OutIcon.m_Texture = InTexture;
		OutIcon.U = 0.f;
		OutIcon.V = 0.f;
		OutIcon.UL = 1.f;
		OutIcon.VL = 1.f;
		OutIcon.Size = { InTexture->GetWidth(), InTexture->GetHeight() };

		return OutIcon;

	}

}
