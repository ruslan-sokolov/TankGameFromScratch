#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Framework2D/Graphic2D/Render/ResourceLoader.h>
#include <Framework2D/Structs/Vectors.h>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <vector>

namespace Framework2D
{
	class FRAMEWORK2D_API RendererStatics
	{
	public:
		static glm::vec3 Translation;
		static glm::mat4 IdentityMatrix;

		static glm::mat4 Proj;
		static glm::mat4 View;
		static glm::mat4 Model;

		static glm::mat4 ProjViewModel;

		inline static void Init(float Width, float Height);
	};

	struct FRAMEWORK2D_API VertexBatchTexture
	{
		Vec2 Position;
		Vec4 Color;
		Vec2 TexCoord;
		float TextureSlot;
	};

	struct FRAMEWORK2D_API VertexBatchTextureQuad
	{
		VertexBatchTexture Vertices[4];
	};

	struct FRAMEWORK2D_API VertexBatchColor
	{
		Vec2 Position;
		Vec4 Color;
	};

	struct FRAMEWORK2D_API VertexBatchColorQuad
	{
		VertexBatchColor Vertices[4];
	};

	template <typename T>  // primary template
	class FRAMEWORK2D_API Renderer
	{
		unsigned int QuadVA;
		unsigned int QuadVB;
		unsigned int QuadIB;

		Shader* shader;

		mutable std::vector<uint32_t> Indicies;
		mutable std::vector<T> VertQuads;

		inline void ResetIndicies(unsigned int QuadNum);
		inline void PushIndex();

	public:
		inline Renderer() = delete;  // use specialization only
		inline ~Renderer();

		inline void ResetVertexQuads(unsigned int QuadNum);
		inline void PushVertexQuad(T& VertQuad);
		inline void PushVertexQuad(T&& VertQuad);
		//inline void CreateAndPushVertexQuad() const = delete;

		inline void Draw() const; 
	};

	// VertexBatchColorQuad Specialization
	template<> inline Renderer<VertexBatchColorQuad>::Renderer();
	//template<> void Renderer<VertexBatchColorQuad>::CreateAndPushVertexQuad(int s) const;

	// VertexBatchTextureQuad Specialization
	template<> inline Renderer<VertexBatchTextureQuad>::Renderer();
	//template<> void Renderer<VertexBatchTextureQuad>::CreateAndPushVertexQuad() const;

	template <typename T> inline Renderer<T>::~Renderer()
	{
		glDeleteBuffers(1, &QuadIB);  // delete ib
		glDeleteBuffers(1, &QuadVB);  // delete vb
		glDeleteVertexArrays(1, &QuadVA);  // delete va
	}

	template <typename T> inline void Renderer<T>::ResetIndicies(unsigned int QuadNum)
	{
		Indicies.clear();
		Indicies.reserve(QuadNum * 6);
	}

	template <typename T> inline void Renderer<T>::PushIndex()
	{
		unsigned int QuadNum = Indicies.size() / 6 * 4;
		uint32_t IndexArr[6] = { QuadNum + 0, QuadNum + 1, QuadNum + 2, QuadNum + 2, QuadNum + 3, QuadNum + 0 };
		std::copy(IndexArr, IndexArr + 6, std::back_inserter(Indicies));
	}

	template <typename T> inline void Renderer<T>::ResetVertexQuads(unsigned int QuadNum)
	{
		VertQuads.clear();
		VertQuads.reserve(QuadNum);
		ResetIndicies(QuadNum);
	}

	template <typename T> inline void Renderer<T>::PushVertexQuad(T& VertQuad)
	{
		VertQuads.push_back(VertQuad);
		PushIndex();
	}

	template <typename T> inline void Renderer<T>::PushVertexQuad(T&& VertQuad)
	{
		VertQuads.push_back(VertQuad);
		PushIndex();
	}

	template <typename T> inline void Renderer<T>::Draw() const
	{
		if (VertQuads.size() == 0) return;

		glBindVertexArray(QuadVA);  // bind vertex array

		glBindBuffer(GL_ARRAY_BUFFER, QuadVB);  // initialize vertex buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * VertQuads.size(),
			(const void*)VertQuads.data(), GL_STREAM_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadIB);  // initialize vertex index buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * Indicies.size(),
			(const void*)Indicies.data(), GL_STREAM_DRAW);

		shader->Bind();

		glDrawElements(GL_TRIANGLES, 6 * VertQuads.size(), GL_UNSIGNED_INT, NULL);  // draw call
	}

	// VertexBatchColorQuad Specialization
	template<> inline Renderer<VertexBatchColorQuad>::Renderer() : QuadVA(0), QuadVB(0), QuadIB(0)
	{
		glGenVertexArrays(1, &QuadVA);  // generate vertex array
		glBindVertexArray(QuadVA);

		glGenBuffers(1, &QuadVB); // generate vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, QuadVB);

		glEnableVertexAttribArray(0); // vertex buffer layout
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexBatchColor),
			(const void*)offsetof(VertexBatchColor, Position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBatchColor),
			(const void*)offsetof(VertexBatchColor, Color));

		glGenBuffers(1, &QuadIB); // generate index buffer

		shader = ResourceLoader::GetShader(ShaderType::QuadBatchColor);
	}

	// VertexBatchTextureQuad Specialization
	template<> inline Renderer<VertexBatchTextureQuad>::Renderer() : QuadVA(0), QuadVB(0), QuadIB(0)
	{
		glGenVertexArrays(1, &QuadVA); // generate vertex array
		glBindVertexArray(QuadVA);

		glGenBuffers(1, &QuadVB); // generate vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, QuadVB);

		glEnableVertexAttribArray(0); // vertex buffer layout
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexBatchTexture),
			(const void*)offsetof(VertexBatchTexture, Position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBatchTexture),
			(const void*)offsetof(VertexBatchTexture, Color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexBatchTexture),
			(const void*)offsetof(VertexBatchTexture, TexCoord));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(VertexBatchTexture),
			(const void*)offsetof(VertexBatchTexture, TextureSlot));

		glGenBuffers(1, &QuadIB);  // generate index buffer

		shader = ResourceLoader::GetShader(ShaderType::QuadBatchTexture);
	}
}