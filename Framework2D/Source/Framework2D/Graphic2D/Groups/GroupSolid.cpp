#include "PCH_Framework.h"
#include "GroupSolid.h"
#include <Framework2D/Graphic2D/Entities/SolidEntity.h>

#include <GL/glew.h>
#include "glm/gtc/matrix_transform.hpp"

#include <Framework2D/Graphic2D/Render/ResourceLoader.h>

namespace Framework2D {

	static glm::mat4 IdentityMatrix{ 1.0f };
	
	static glm::vec3 Translation{ 0.0f, 0.0f, 0.0f };

	static glm::mat4 Proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
	static glm::mat4 View = glm::translate(IdentityMatrix, { 0.0f, 0.0f, 0.0f });
	static glm::mat4 Model = glm::translate(IdentityMatrix, Translation);
	
	static glm::mat4 ProjViewModel = Proj * View * Model;

	GroupSolid::GroupSolid(const std::string& GroupName)
		: Group(GroupName), QuadVA(0), QuadVB(0), QuadIB(0)
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

		// get shader ref
		shader = ResourceLoader::GetShader(ShaderType::QuadBatchColor);
		// set uniform
		shader->Bind();
		shader->SetUniformMat4f("u_ViewProjModel", ProjViewModel);
		shader->Unbind();
	}

	GroupSolid::~GroupSolid()
	{
		// delete ib
		glDeleteBuffers(1, &QuadIB);

		// delete vb
		glDeleteBuffers(1, &QuadVB);

		// delete va
		glDeleteVertexArrays(1, &QuadVA);
	}

	void GroupSolid::OnUpdate(float DeltaTime)
	{
		for (auto& Solid : Entities)
		{
			Solid->OnUpdate(DeltaTime);
		}
	}

	void GroupSolid::OnEvent(Engine::Event& e)
	{
		for (auto it = Entities.end(); it != Entities.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}

	void GroupSolid::OnDraw()
	{
		std::vector<VertexBatchColorQuad> VertQuads;
		VertQuads.reserve(Entities.size());

		std::vector<uint32_t> Indicies;
		Indicies.reserve(Entities.size() * 6);

		unsigned short int VertCount = 0;
		SolidEntity* Solid;
		for (auto& Entity : Entities)
		{
			// check if should render
			if (!Entity->IsRenderEnabled())
				continue;

			// get vertex buffer data
			Solid = static_cast<SolidEntity*>(Entity);
			VertQuads.push_back(std::move(Solid->GetVertexQuad()));

			// gen index buffer data
			uint32_t IndexArr[6] = { VertCount + 0, VertCount + 1 , VertCount + 2, VertCount + 2, VertCount + 3, VertCount + 0 };
			std::copy(IndexArr, IndexArr + 6, std::back_inserter(Indicies));
			VertCount += 4;
		}

		// Check if we have any elements to draw
		if (VertQuads.size() == 0)
			return;

		// bind vertex array
		glBindVertexArray(QuadVA);

		// initialize vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, QuadVB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBatchColorQuad) * VertQuads.size(), 
			(const void*)VertQuads.data(), GL_STREAM_DRAW);

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
			ENGINE_LOG(error, "[GroupSolid::OnDraw()] Can't locate shader");
			return;
		}

		// draw
		glDrawElements(GL_TRIANGLES, 6 * VertQuads.size(), GL_UNSIGNED_INT, NULL);
	}

	bool GroupSolid::AddSolid(SolidEntity* Solid)
	{
		return Group::AddEntity(Solid);
	}

	bool GroupSolid::RemoveSolid(SolidEntity* Solid)
	{
		return Group::RemoveEntity(Solid);
	}

	SolidEntity* GroupSolid::GetSolid(const std::string& SolidName)
	{
		return static_cast<SolidEntity*>(Group::FindEntity(SolidName));
	}

	bool GroupSolid::HasSolid(const std::string& SolidName)
	{
		return Group::FindEntity(SolidName) != nullptr;
	}
}