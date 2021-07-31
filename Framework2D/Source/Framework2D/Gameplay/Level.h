#pragma once
#include <Framework2D/Framework2DAPI.h>

#include <Framework2D/Structs/Vectors.h>
#include <string>
#include <unordered_set>

#include <Framework2D/Gameplay/Actor/Actor.h>

namespace Framework2D {	
	
	class Actor;
	class GameMode;
	class LayerGameplay;

	class FRAMEWORK2D_API Level
	{
		friend class GameMode;
		friend class LayerGameplay;

		// should be called in GM, calls tick for actors and level
		inline void Update(float DeltaTime);

		std::unordered_set <Actor*> Actors;
		GameMode* GM_Owner = nullptr;

	public: 
		Level();
		virtual ~Level();

		template<class T>
		T* SpawnActorFromClass(const std::string& Name, const VecInt2D& Pos, Anchor Anchor = Anchor::TOP_LEFT)
		{
			T* SpawnedActor = new T(Name, Pos);

			// anchor pos offset
			SpawnedActor->SetPosition(Pos - GetAnchorOffset(SpawnedActor->GetSize(), Anchor));
			
			SpawnedActor->LevelOwner = this;
			Actors.insert(SpawnedActor);

			GAME_LOG(warn, "Spawned Actor: {}_{}", SpawnedActor->GetName(), SpawnedActor->GetId());
			return SpawnedActor;
		}

		inline void RemoveActor(Actor* ActorToRemove);
		
		inline GameMode* GetGameMode() const { return GM_Owner; }

		virtual void OnTick(float DeltaTime) {};

		// todo: get actors of class
		// todo: get actor by name

	};


}
