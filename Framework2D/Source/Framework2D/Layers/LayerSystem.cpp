#include <PCH_Framework.h>
#include "LayerSystem.h"

#include "Framework2D/Systems/SystemCollision.h"
#include "Framework2D/Systems/SystemInput.h"
#include "Framework2D/Systems/SystemTimer.h"

namespace Framework2D {

	LayerSystem::LayerSystem(const std::string& LayerName)
		: Layer(LayerName)
	{
	}

	LayerSystem::~LayerSystem()
	{
		SystemTimer::RemoveAllTimers();
		SystemInput::RemoveAllBinds();
		SystemCollision::ClearCheckCollisionSet();
	}

	void LayerSystem::OnUpdate(float DeltaTime)
	{
		SystemTimer::UpdateTimers(DeltaTime);
		SystemCollision::CheckCollisionAll();
	}

	void LayerSystem::OnEvent(Engine::Event& e)
	{
		if (e.IsInCategory(Engine::EventCategory::EventCategoryInput))
			SystemInput::OnInputEvent(e);
	}

}
