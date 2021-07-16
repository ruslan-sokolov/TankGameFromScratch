#include <PCH_Framework.h>
#include "ResourceLoader.h"

namespace Framework2D {

	std::unordered_map<std::string, Texture> ResourceLoader::LoadedTextures;
	std::unordered_map<ShaderType, Shader> ResourceLoader::ShaderCache;

	inline void ResourceLoader::LoadTexture(const std::string& Path)
	{
		Texture TempTexture = Texture(Path);
		
		if (TempTexture.IsValid())
		{
			LoadedTextures.try_emplace(Path, TempTexture);
			ENGINE_LOG(info, "[Framework2D::ResourceLoader] Texture {0} loaded", Path);
		}
		else
		{
			ENGINE_LOG(error, "[Framework2D::ResourceLoader] Can't load {0} Texture", Path);
		}
	}

	inline void ResourceLoader::UnloadTexture(const std::string& Path)
	{
		if (LoadedTextures.find(Path) != LoadedTextures.end())
			LoadedTextures.erase(Path);
	}

	inline Texture* ResourceLoader::GetTexture(const std::string& Path)
	{
		// Load texture on demand
		if (LoadedTextures.find(Path) == LoadedTextures.end())
			LoadTexture(Path);

		if (LoadedTextures.find(Path) == LoadedTextures.end())
			return nullptr;

		return &LoadedTextures.at(Path);
	}

	inline void ResourceLoader::RegisterShader(ShaderType Type, const std::string Path)
	{
		ShaderCache.try_emplace(Type, Shader(Path));
		ENGINE_LOG(info, "[Framework2D::ResourceLoader] Shader {0} loaded", Path);
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