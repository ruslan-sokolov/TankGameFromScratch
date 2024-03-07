#include <PCH_Framework.h>
#include "Shader.h"
#include "LogGL.h"

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
		GLCall(glUseProgram(RendererID));
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

	GLuint Shader::CompileShader(GLuint Type, const std::string& Source)
	{
		GLCall(GLuint Id = glCreateShader(Type);)
		const char* Src = Source.c_str();
		const GLint SrcLen = Source.length();
		GLCall(glShaderSource(Id, 1, &Src, &SrcLen);)  //(GLuint shader, GLsizei count, const GLchar *const* string, const GLint* length);
		GLCall(glCompileShader(Id);)

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

	GLuint Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader, bool& bIsSuccess)
	{
		
		GLCall(const GLuint Program = glCreateProgram();)
		GLuint VS_ID = CompileShader(GL_VERTEX_SHADER, VertexShader);
		GLuint FS_ID = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

		GLint Ret;
		CheckShaderError(VS_ID, GL_COMPILE_STATUS, &Ret, "Failed to compile vertex shader!");
		CheckShaderError(FS_ID, GL_COMPILE_STATUS, &Ret, "Failed to compile fragment shader!");
		
		bIsSuccess = VS_ID != 0 && FS_ID != 0;

		GLCall(glAttachShader(Program, VS_ID);)
		GLCall(glAttachShader(Program, FS_ID);)
		GLCall(glLinkProgram(Program);)
		CheckShaderError(Program, GL_LINK_STATUS, &Ret, "Failed to link program!");
		GLCall(glValidateProgram(Program);)

		GLCall(glDeleteShader(VS_ID);)
		GLCall(glDeleteShader(FS_ID);)

		return Program;
	}

	void Shader::CheckShaderError(GLuint Id, GLuint Type, GLint* Ret, const char* OnFail)
	{
		switch(Type)
		{
		case(GL_COMPILE_STATUS):
			glGetShaderiv(Id, Type, Ret);
			if (*Ret == false)
			{
				GLint Length;
				glGetShaderiv(Id, GL_INFO_LOG_LENGTH, &Length);
				GLchar* Msg = new GLchar[Length];
				GLsizei CharsWritten = 0;
				glGetShaderInfoLog(Id, Length, &CharsWritten, Msg);
				ENGINE_LOG(error, "{0}\n\t{1}", OnFail, Msg);
				delete[] Msg;
			}
			break;
		case (GL_LINK_STATUS):
			glGetProgramiv(Id, Type, Ret);
			if (*Ret == false)
			{
				GLint Length;
				glGetProgramiv(Id, GL_INFO_LOG_LENGTH, &Length);
				GLchar* Msg = new GLchar[Length];
				GLsizei CharsWritten = 0;
				glGetProgramInfoLog(Id, Length, &CharsWritten, Msg);
				ENGINE_LOG(error, "{0}\n\t{1}", OnFail, Msg);
				delete[] Msg;
			}
			break;
		default:
			break;
		}
	}

	// --------------------------------------------------------
}
