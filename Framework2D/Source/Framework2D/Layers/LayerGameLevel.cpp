#include <PCH_Framework.h>
#include "LayerGameLevel.h"

#include <Framework2D/Gameplay/Level.h>
#include <Framework2D/Gameplay/Actor/Actor.h>

namespace Framework2D
{
	LayerGameLevel::LayerGameLevel(const std::string& LayerName)
		: Layer(LayerName)
	{
	}

	LayerGameLevel::~LayerGameLevel()
	{
	}

	void LayerGameLevel::OnUpdate(float DeltaTime)
	{
		if (CurrentLevel)
		{
			for (auto& A : CurrentLevel->Actors)
				A->OnTick(DeltaTime);
		}

	}

}
