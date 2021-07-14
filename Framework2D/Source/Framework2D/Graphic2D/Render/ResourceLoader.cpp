#include <PCH_Framework.h>
#include "ResourceLoader.h"

namespace Framework2D {

	std::unordered_map<std::string, Texture> ResourceLoader::LoadedTextures;
	std::unordered_map<ShaderType, Shader> ResourceLoader::ShaderCache;

	inline void ResourceLoader::LoadTexture(const std::string& Path)
	{
		LoadedTextures.try_emplace(Path, Texture(Path));
	}

	inline void ResourceLoader::UnloadTexture(const std::string& Path)
	{
		if (LoadedTextures.find(Path) != LoadedTextures.end())
			LoadedTextures.erase(Path);
	}

	inline Texture* ResourceLoader::GetTexture(const std::string& Path)
	{
		if (LoadedTextures.find(Path) == LoadedTextures.end())
			return nullptr;

		return &LoadedTextures.at(Path);
	}

	inline void ResourceLoader::RegisterShader(ShaderType Type, const std::string Path)
	{
		ShaderCache.try_emplace(Type, Shader(Path));
	}

	inline void ResourceLoader::DeleteShader(ShaderType Type)
	{
		if (ShaderCache.find(Type) != ShaderCache.end())
			ShaderCache.erase(Type);
	}

	inline Shader* ResourceLoader::GetShader(ShaderType Type)
	{
		if (ShaderCache.find(Type) == ShaderCache.end())
			return nullptr;

		return &ShaderCache.at(Type);
	}

}