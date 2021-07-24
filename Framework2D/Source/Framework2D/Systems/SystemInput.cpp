#include "PCH_Framework.h"
#include "SystemInput.h"

namespace Framework2D {

	void SystemInput::OnInputEvent(Engine::Event& e)
	{
		ENGINE_LOG(info, "[System Input] Event: {}", e);
	}
}


