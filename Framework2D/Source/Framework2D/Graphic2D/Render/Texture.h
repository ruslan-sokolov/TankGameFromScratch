#pragma once

#include "Framework2D/Framework2DAPI.h"

#include <string>

namespace Framework2D {

	class ResourceLoader;

	class FRAMEWORK2D_API Texture
	{
		friend class ResourceLoader;

		const std::string FilePath;

		unsigned int RendererID;

		unsigned char* ImageCache;

		int Width, Height, BPP;

		mutable int ActiveSlot;

		bool bIsValid;

	public:
		
		~Texture();

		bool IsValid() const { return bIsValid; }

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return Width; }
		inline int GetHeight() const { return Height; }
		
		inline int GetActiveSlot() const { return ActiveSlot; }

		static int GetMaxTextureBind();

	protected:

		Texture(const std::string& Path);
	};

}