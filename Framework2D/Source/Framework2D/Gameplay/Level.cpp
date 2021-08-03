#include <PCH_Framework.h>
#include "Level.h"



namespace Framework2D {

	inline void Level::RemoveActor(Actor* ActorToRemove)
	{
		if (Actors.find(ActorToRemove) != Actors.end())
		{
			Actors.erase(ActorToRemove);
			ActorPendToKill(ActorToRemove);

			GAME_LOG(warn, "DestroyedActor: {}_{}", ActorToRemove->GetName(), ActorToRemove->GetId());
		}
	}

	inline void Level::Update(float DeltaTime)
	{
		DeletePendingKillActors();
		
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
