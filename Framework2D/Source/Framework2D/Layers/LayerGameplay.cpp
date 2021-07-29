#include <PCH_Framework.h>
#include "LayerGameplay.h"

#include <Framework2D/Gameplay/GameMode.h>

namespace Framework2D
{
	LayerGameplay::LayerGameplay(const std::string& LayerName)
		: Layer(LayerName)
	{
	}

	LayerGameplay::~LayerGameplay()
	{
	}

	void LayerGameplay::OnUpdate(float DeltaTime)
	{
		if (GM) GM->Update(DeltaTime);
	}

}
