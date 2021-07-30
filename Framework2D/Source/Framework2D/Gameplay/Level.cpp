#include <PCH_Framework.h>
#include "Level.h"



namespace Framework2D {

	inline void Level::RemoveActor(Actor* ActorToRemove)
	{
		if (Actors.find(ActorToRemove) != Actors.end())
			Actors.erase(ActorToRemove);
	}

	inline void Level::Update(float DeltaTime)
	{
		for (auto& A : Actors) A->Update(DeltaTime);
		Level::OnTick(DeltaTime);
	}

	Level::Level()
	{
	}
	
	Level::~Level()
	{
		for (auto& A : Actors) delete A;
	}
}
