#include <PCH_Framework.h>
#include "Shader.h"

namespace Framework2D {

	Shader::Shader(const std::string& Path)
		: FilePath(Path), RendererID(0)
	{
		ShaderProgramSource Source = ParseShader(FilePath, bSuccessfullyCreated);
		if (bSuccessfullyCreated)
			RendererID = CreateShader(Source.VertexSource, Source.FragmentSource, bSuccessfullyCreated);
	}

	Shader::Shader(Shader&& s) noexcept
		: FilePath(std::move(s.FilePath)), RendererID(s.RendererID), 
		UniformLocationCache(std::move(s.UniformLocationCache)), bSuccessfullyCreated(s.bSuccessfullyCreated)
	{
		s.RendererID = 0;
	}

	Shader::~Shader()
	{
		if (RendererID != 0)
			glDeleteProgram(RendererID);
	}

	inline void Shader::Bind()
	{
		glUseProgram(RendererID);
	}

	inline void Shader::Unbind()
	{
		glUseProgram(0);
	}

	inline void Shader::SetUniform1i(const std::string& Name, int Value)
	{
		glUniform1i(GetUniformLocation(Name), Value);
	}

	inline void Shader::SetUniform1iv(const std::string& Name, int Count, int* Values)
	{
		glUniform1iv(GetUniformLocation(Name), Count, Values);
	}

	inline void Shader::SetUniform1f(const std::string& Name, float Value)
	{
		glUniform1f(GetUniformLocation(Name), Value);
	}

	inline void Shader::SetUniform4f(const std::string& Name, float V0, float V1, float V2, float V3)
	{
		glUniform4f(GetUniformLocation(Name), V0, V1, V2, V3);
	}

	inline void Shader::SetUniform4f(const std::string& Name, const float Arr[4])
	{
		glUniform4f(GetUniformLocation(Name), Arr[0], Arr[1], Arr[2], Arr[3]);
	}

	inline void Shader::SetUniformMat4f(const std::string& Name, const glm::mat4& Matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(Name), 1, GL_FALSE, &Matrix[0][0]);
	}

	inline GLint Shader::GetUniformLocation(const std::string& Name) const
	{
		if (UniformLocationCache.find(Name) != UniformLocationCache.end())
			return UniformLocationCache.at(Name);

		GLint Location = glGetUniformLocation(RendererID, Name.c_str());
		if (Location == -1)
		{
			ENGINE_LOG(error, "Uniform location {0} doesn't exists!");
		}
		else
		{
			UniformLocationCache.emplace(Name, Location);
		}

		return Location;
	}

	// static ----------------------------------------------------
	ShaderProgramSource Shader::ParseShader(const std::string& FilePath, bool& bIsSuccess)
	{
		std::string Line;
		std::stringstream SS[2];
		ShaderSourceType Type = ShaderSourceType::NONE;

		std::ifstream FileStream(FilePath);

		// check if can read file;
		if (FileStream.fail())
		{
			bIsSuccess = false;
			ENGINE_LOG(trace, "Failed to parse shader {0}, Exception open/read/close file", FilePath);
			return ShaderProgramSource();
		}

		while (getline(FileStream, Line))
		{
			if (Line.find("#shader") != std::string::npos)
			{
				if (Line.find("vertex") != std::string::npos) Type = ShaderSourceType::VERTEX;
				else if (Line.find("fragment") != std::string::npos) Type = ShaderSourceType::FRAGMENT;
			}
			else
			{
				SS[(unsigned int)Type] << Line << "\n";
			}
		}

		bIsSuccess = true;
		return { SS[0].str(), SS[1].str() };
	}

	unsigned int Shader::CompileShader(unsigned int Type, const std::string& Source)
	{
		unsigned int Id = glCreateShader(Type);
		const char* Src = Source.c_str();
		glShaderSource(Id, 1, &Src, NULL);
		glCompileShader(Id);

		// error handle
		int Result;
		glGetShaderiv(Id, GL_COMPILE_STATUS, &Result);
		if (Result == GL_FALSE)
		{
			int Length;
			glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &Length);
			char* Msg = new char[Length];
			glGetShaderInfoLog(Id, Length, &Length, Msg);
			ENGINE_LOG(error, "Failed to compile {0} shader!", Type == GL_VERTEX_SHADER ? "vertex" : "fragment");
			ENGINE_LOG(error, "{0}", Msg);
			delete[] Msg;

			glDeleteShader(Id);
			return 0;
		}  //

		return Id;
	}

	unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader, bool& bIsSuccess)
	{
		
		unsigned int Program = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

		bIsSuccess = vs != 0 && fs != 0;

		glAttachShader(Program, vs);
		glAttachShader(Program, fs);
		glLinkProgram(Program);
		glValidateProgram(Program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return Program;
	}
	// --------------------------------------------------------
}
