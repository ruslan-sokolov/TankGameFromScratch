#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Framework2D/Graphic2D/Render/ResourceLoader.h>
#include <Framework2D/Structs/Vectors.h>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Vertex.h"

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

	template <typename T>  // primary template
	class FRAMEWORK2D_API Renderer
	{
		unsigned int QuadVA = 0;
		unsigned int QuadVB = 0;
		unsigned int QuadIB = 0;

		Shader* shader;
		
		std::vector<uint32_t> Indicies;
		std::vector<T> VertQuads;

		inline void ResetIndicies(unsigned int QuadNum);
		inline void PushIndex();

	public:
		inline Renderer() = delete;  // use specialization only
		inline ~Renderer();

		inline void ResetVertexQuads(unsigned int QuadNum);
		inline void PushVertexQuad(const T& VertQuad);
		inline void PushVertexQuad(T&& VertQuad);
		
		// todo: try std::forward<Args>(args)...
		template <typename... Args>  // variadic args template for definition in each specializtion
		inline void CreateAndPushVertexQuad(Args&& ... args) = delete;

		inline void Draw() const; 
	};

	// VertexBatchColorQuad Specialization declaration
	template<> inline Renderer<VertexBatchColorQuad>::Renderer()
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

	template<> template<> 
	inline void Renderer<VertexBatchColorQuad>::CreateAndPushVertexQuad(Vec2&& Position, Vec2&& Size, Vec4&& Color)
	{
		VertexBatchColor V_0 {Position,                                   Color};
		VertexBatchColor V_1{ {Position.X + Size.X, Position.Y},          Color };
		VertexBatchColor V_2{ {Position.X + Size.X, Position.Y + Size.Y}, Color };
		VertexBatchColor V_3{ {Position.X,          Position.Y + Size.Y}, Color };

		VertexBatchColorQuad Quad = { V_0, V_1, V_2, V_3 };
		PushVertexQuad(std::move(Quad));
	}  //

	// VertexBatchTextureQuad Specialization declaration
	template<> inline Renderer<VertexBatchTextureQuad>::Renderer()
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
	
	template<> template<> 
	inline void Renderer<VertexBatchTextureQuad>::CreateAndPushVertexQuad(Vec2&& Position, Vec2&& Size, Vec4&& Color, float&& TexSlot)
	{
		VertexBatchTexture V_0 {Position,                                   Color, {0, 1}, TexSlot};
		VertexBatchTexture V_1{ {Position.X + Size.X, Position.Y},          Color, {1, 1}, TexSlot };
		VertexBatchTexture V_2{ {Position.X + Size.X, Position.Y + Size.Y}, Color, {1, 0}, TexSlot };
		VertexBatchTexture V_3{ {Position.X,          Position.Y + Size.Y}, Color, {0, 0}, TexSlot };

		VertexBatchTextureQuad Quad{ V_0, V_1, V_2, V_3 };
		PushVertexQuad(std::move(Quad));
	} //

	// Primary Template Methods definitions:
	template <typename T> inline Renderer<T>::~Renderer()
	{
		glDeleteBuffers(1, &QuadIB);  // delete ib
		glDeleteBuffers(1, &QuadVB);  // delete vb
		glDeleteVertexArrays(1, &QuadVA);  // delete va
	}

	template <typename T> inline void Renderer<T>::ResetIndicies(unsigned int QuadNum)
	{
		Indicies.clear();
		Indicies.reserve((size_t)(6 * QuadNum));
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

	template <typename T> inline void Renderer<T>::PushVertexQuad(const T& VertQuad)
	{
		VertQuads.emplace_back(VertQuad);
		PushIndex();
	}

	template <typename T> inline void Renderer<T>::PushVertexQuad(T&& VertQuad)
	{
		VertQuads.emplace_back(std::move(VertQuad));
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

		glDrawElements(GL_TRIANGLES, Indicies.size(), GL_UNSIGNED_INT, NULL);  // draw call
	}  //

}
