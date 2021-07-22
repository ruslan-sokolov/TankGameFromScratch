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

		/*
		 *  0 - reserved for Texture404
		 *  0 < n < max_slots - actual slot range
		 */
		mutable uint32_t ActiveSlot;

		bool bSuccessfullyCreated;

		explicit Texture(const std::string& Path);
		Texture(const Texture&) = delete;
		Texture& operator=(Texture&) = delete;
		Texture& operator=(Texture&&) = delete;

		static inline Texture* Texture404 = nullptr;

	public:
		Texture(Texture&& t) noexcept;
		~Texture();

		inline bool IsSuccessfullyCreated() const{ return bSuccessfullyCreated; }

		/** Actual bind slot will be plus one, zero slot reserved for Texture404 */
		void Bind(int32_t slot = 0) const;
		void Unbind() const;

		inline int GetWidth() const { return Width; }
		inline int GetHeight() const { return Height; }
		inline const std::string& GetPath() const { return FilePath; }
		
		inline uint32_t GetActiveSlot() const { return ActiveSlot; }

		static int GetMaxTextureBind();
	};

}