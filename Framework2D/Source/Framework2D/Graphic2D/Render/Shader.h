#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <string>
#include <unordered_map>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace Framework2D {

	class ResourceLoader;

	enum class ShaderSourceType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class FRAMEWORK2D_API Shader
	{
		friend class ResourceLoader;

		std::string FilePath;
		unsigned int RendererID;

		// uniform location cache
		mutable std::unordered_map<std::string, GLint> UniformLocationCache;
		
		bool bSuccessfullyCreated;

		explicit Shader(const std::string& Path);
		Shader(const Shader&) = delete;
		Shader& operator=(Shader&) = delete;
		Shader& operator=(Shader&&) = delete;

	public:
		Shader(Shader&& s) noexcept;
		~Shader();

		bool IsSuccessfullyCreated() { return bSuccessfullyCreated; }

		inline void Bind();
		inline void Unbind();

		// Set uniforms
		inline void SetUniform1i(const std::string& Name, int Value);
		inline void SetUniform1iv(const std::string& Name, int Count, int* Values);
		inline void SetUniform1f(const std::string& Name, float Value);
		inline void SetUniform4f(const std::string& Name, float V0, float V1, float V2, float V3);
		inline void SetUniform4f(const std::string& Name, const float Arr[4]);
		inline void SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix);

	private:
		// Get uniform location from cache if exists or get from gpu mem and cache it
		inline GLint GetUniformLocation(const std::string& Name) const;

		static ShaderProgramSource ParseShader(const std::string& FilePath, bool& bIsSuccess);
		static unsigned int CompileShader(unsigned int Type, const std::string& Source);
		static unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader, bool& bIsSuccess);

	};

}
