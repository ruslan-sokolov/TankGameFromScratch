#include <PCH_Framework.h>
#include "GroupSprite.h"
#include <Framework2D/Graphic2D/Entities/SpriteEntity.h>

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

namespace Framework2D {

	static glm::mat4 IdentityMatrix{ 1.0f };

	static glm::vec3 Translation{ 0.0f, 0.0f, 0.0f };

	static glm::mat4 Proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
	static glm::mat4 View = glm::translate(IdentityMatrix, { 0.0f, 0.0f, 0.0f });
	static glm::mat4 Model = glm::translate(IdentityMatrix, Translation);

	static glm::mat4 ProjViewModel = Proj * View * Model;

	GroupSprite::GroupSprite(const std::string& GroupName)
		: Group(GroupName), QuadVA(0), QuadVB(0), QuadIB(0)
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
		glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, sizeof(VertexBatchTexture),
			(const void*)offsetof(VertexBatchTexture, TextureSlot));
		
		glGenBuffers(1, &QuadIB);  // generate index buffer

		// get shader ref
		shader = ResourceLoader::GetShader(ShaderType::QuadBatchTexture);
		// set uniform
		shader->Bind();
		shader->SetUniformMat4f("u_ViewProjModel", ProjViewModel);
		shader->Unbind();
	}

	void GroupSprite::OnUpdate(float DeltaTime)
	{
		for (auto& Sprite : Entities)
		{
			Sprite->OnUpdate(DeltaTime);
		}
	}

	void GroupSprite::OnEvent(Engine::Event& e)
	{
		for (auto it = Entities.end(); it != Entities.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}

	void GroupSprite::OnDraw()
	{
		std::vector<VertexBatchTextureQuad> VertexQuads;
		VertexQuads.reserve(Entities.size());

		std::vector<uint32_t> Indicies;
		Indicies.reserve(Entities.size() * 6);

		unsigned short int VertCount = 0;
		SpriteEntity* Sprite;
		for (auto& Entity : Entities)
		{
			// check if should render
			if (!Entity->IsRenderEnabled())
				continue;

			// get vertex buffer data
			Sprite = static_cast<SpriteEntity*>(Entity);
			VertexQuads.push_back(std::move(Sprite->GetVertexQuad()));

			// gen index buffer data
			uint32_t IndexArr[6] = { VertCount + 0, VertCount + 1, VertCount + 2, VertCount + 2, VertCount + 3, VertCount + 0 };
			std::copy(IndexArr, IndexArr + 6, std::back_inserter(Indicies));
			VertCount += 4;
		}

		// Check if we have any elements to draw
		if (VertexQuads.size() == 0)
			return;

		// bind vertex array
		glBindVertexArray(QuadVA);
		
		// initialize vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, QuadVB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBatchTextureQuad) * VertexQuads.size(),
			(const void*)VertexQuads.data(), GL_STREAM_DRAW);

		// initialize vertex index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadIB);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * Indicies.size(), 
			(const void*)Indicies.data(), GL_STREAM_DRAW);

		// bind shader
		if (shader)
		{
			shader->Bind();
		}
		else
		{
			ENGINE_LOG(error, "{GroupSprite::OnDraw()] Can't locate shader");
			return;
		}

		// draw
		glDrawElements(GL_TRIANGLES, 6 * VertexQuads.size(), GL_UNSIGNED_INT, NULL);
	}

	bool GroupSprite::AddSprite(SpriteEntity* spriteEntity)
	{
		return Group::AddEntity(spriteEntity);
	}

	bool GroupSprite::RemoveSprite(SpriteEntity* spriteEntity)
	{
		return Group::RemoveEntity(spriteEntity);
	}

	SpriteEntity* GroupSprite::GetSprite(const std::string& SpriteName)
	{
		return static_cast<SpriteEntity*>(Group::FindEntity(SpriteName));
	}

	bool GroupSprite::HasSprite(const std::string& SpriteName)
	{
		return GetSprite(SpriteName) != nullptr;
	}
}