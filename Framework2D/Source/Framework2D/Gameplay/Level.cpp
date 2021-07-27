#include <PCH_Framework.h>
#include "Level.h"

#include <Framework2D/Gameplay/Actor/Actor.h>
#include <Framework2D/Layers/LayerGameLevel.h>

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

	Level::Level(GameMode* GM_Owner)
		: GM_Owner(GM_Owner)
	{
		// todo: move somewhere else
		if (Game2D* Game = GetGame()) Game->GetGameLevelLayer()->SetLevel(this);
	}
	
	Level::~Level()
	{
	}
}
