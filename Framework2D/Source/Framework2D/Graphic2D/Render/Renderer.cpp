#include <PCH_Framework.h>
#include "Renderer.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Framework2D {

	glm::mat4 RendererStatics::IdentityMatrix{ 1.0f };
	glm::vec3 RendererStatics::Translation{ 0.0f, 0.0f, 0.0f };

	glm::mat4 RendererStatics::Proj = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
	glm::mat4 RendererStatics::View = glm::translate(IdentityMatrix, { 0.0f, 0.0f, 0.0f });
	glm::mat4 RendererStatics::Model = glm::translate(IdentityMatrix, Translation);

	glm::mat4 RendererStatics::ProjViewModel = Proj * View * Model;

	inline void RendererStatics::Init(float Width, float Height)
	{
		glm::mat4 Proj = glm::ortho(0.0f, Width, Height, 0.0f, -1.0f, 1.0f);
		RendererStatics::ProjViewModel = Proj * View * Model;
	}
}
