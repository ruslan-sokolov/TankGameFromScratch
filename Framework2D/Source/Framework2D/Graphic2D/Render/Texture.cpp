#include <PCH_Framework.h>
#include "Texture.h"

#include <GL/glew.h>
#include <stb_image/stb_image.h>

namespace Framework2D {

	Texture::Texture(const std::string& Path)
		: RendererID(0), FilePath(Path), ImageCache(nullptr), Width(0), Height(0), BPP(0), ActiveSlot(0)
	{
		stbi_set_flip_vertically_on_load(1);
		ImageCache = stbi_load(FilePath.c_str(), &Width, &Height, &BPP, 4);

		// generate and bind texture
		glGenTextures(1, &RendererID);
		glBindTexture(GL_TEXTURE_2D, RendererID);

		// default texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// specify pixel array to texture and unbind texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageCache);
		
		if (ImageCache)
			stbi_image_free(ImageCache);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &RendererID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		ActiveSlot = slot;
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, RendererID);
	}

	void Texture::Unbind() const
	{
		ActiveSlot = 0;
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	int Texture::GetMaxTextureBind()
	{
		int MaxBindTextureUnitsNum;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MaxBindTextureUnitsNum);
		return MaxBindTextureUnitsNum;
	}

}