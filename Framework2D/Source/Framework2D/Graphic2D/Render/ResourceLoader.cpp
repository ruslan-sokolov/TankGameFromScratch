#include <PCH_Framework.h>
#include "ResourceLoader.h"

namespace Framework2D {

	std::unordered_map<std::string, Texture> ResourceLoader::LoadedTextures;
	std::unordered_map<ShaderType, Shader> ResourceLoader::ShaderCache;

	inline void ResourceLoader::LoadTexture(const std::string& Path)
	{
		Texture TempTexture = Texture(Path);

		if (TempTexture.IsSuccessfullyCreated())
		{
			LoadedTextures.try_emplace(Path, std::move(TempTexture));
			ENGINE_LOG(info, "[Framework2D::ResourceLoader] Texture {0} loaded", Path);
		}
		else
		{
			ENGINE_LOG(error, "[Framework2D::ResourceLoader] Texture {0} failed to load", Path);
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
		if (ShaderCache.find(Type) != ShaderCache.end())
		{
			ENGINE_LOG(info, "[Framework2D::ResourceLoader] Shader {0} fail to load, already exists!", Path);
			return;
		}

		Shader TempShader = Shader(Path);
		if (TempShader.IsSuccessfullyCreated()) 
		{
			ShaderCache.emplace(Type, std::move(TempShader));
			ENGINE_LOG(info, "[Framework2D::ResourceLoader] Shader {0} loaded", Path);
		}
		else
		{
			ENGINE_LOG(error, "[Framework2D::ResourceLoader] Shader {0} fail to load!", Path);
		}
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