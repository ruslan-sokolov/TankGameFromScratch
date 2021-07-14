#pragma once

#include "Framework2D/Framework2DAPI.h"

#include <string>
#include <unordered_map>

#include <Framework2D/Graphic2D/Render/Texture.h>
#include <Framework2D/Graphic2D/Render/Shader.h>

namespace Framework2D {

	enum class ShaderType
	{
		QuadBatchTexture,
		QuadBatchColor
	};

	class FRAMEWORK2D_API ResourceLoader
	{
		static std::unordered_map<std::string, Texture> LoadedTextures;
		static std::unordered_map<ShaderType, Shader> ShaderCache;

	public:
		static inline void LoadTexture(const std::string& Path);
		static inline void UnloadTexture(const std::string& Path);

		static inline Texture* GetTexture(const std::string& Path);
		
		static inline void RegisterShader(ShaderType Type, const std::string Path);
		static inline void DeleteShader(ShaderType Type);
		static inline Shader* GetShader(ShaderType Type);
	};

}