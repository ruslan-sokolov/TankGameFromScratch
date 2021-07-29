#include <PCH_Framework.h>
#include "Level.h"

#include <Framework2D/Gameplay/Actor/Actor.h>

namespace Framework2D {
	
	template<typename T>
	inline T* Level::SpawnActorFromClass(const std::string& Name, const VecInt2D& Pos)
	{
		T* SpawnedActor = new T(Name, Pos);
		SpawnedActor->LevelOwner = this;
		Actors.insert(SpawnedActor);
		return SpawnedActor;
	}

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
	}
}
