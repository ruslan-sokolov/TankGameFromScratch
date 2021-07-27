#pragma once

#include "Framework2D/Framework2DAPI.h"

#include <string>
#include <unordered_map>
#include <vector>

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
		static std::string Texture404Path;

		static inline void LoadTexture(const std::string& Path);
		static inline void LoadTexture(const std::initializer_list<const char*>& PathList);
		static inline void UnloadTexture(const std::string& Path);
		static inline Texture* GetTexture(const std::string& Path);
		static inline std::vector<Texture*> GetTextures(const std::initializer_list<const char*>& PathList);

		static inline void BindTextures(std::vector<Texture*>&& Textures);
		
		static inline void RegisterShader(ShaderType Type, const std::string Path);
		static inline void DeleteShader(ShaderType Type);
		static inline Shader* GetShader(ShaderType Type);
	};

}
