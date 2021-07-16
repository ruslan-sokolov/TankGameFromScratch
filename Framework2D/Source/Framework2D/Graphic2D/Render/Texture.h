#pragma once

#include "Framework2D/Framework2DAPI.h"

#include <string>

namespace Framework2D {

	class ResourceLoader;

	class FRAMEWORK2D_API Texture
	{
		friend class ResourceLoader;

		std::string FilePath;

		unsigned int RendererID;

		unsigned char* ImageCache;

		int Width, Height, BPP;

		mutable int ActiveSlot;

		bool bSuccessfullyCreated;

		explicit Texture(const std::string& Path);
		Texture(const Texture&) = delete;
		Texture& operator=(Texture&) = delete;
		Texture& operator=(Texture&&) = delete;

	public:
		Texture(Texture&& t) noexcept;
		~Texture();

		inline bool IsSuccessfullyCreated() const{ return bSuccessfullyCreated; }

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return Width; }
		inline int GetHeight() const { return Height; }
		
		inline int GetActiveSlot() const { return ActiveSlot; }

		static int GetMaxTextureBind();


	};

}