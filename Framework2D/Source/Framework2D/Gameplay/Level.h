#pragma once
#include <Framework2D/Framework2DAPI.h>

#include <Framework2D/Structs/Vectors.h>
#include <Framework2D/Structs/Anchor.h>
#include <Framework2D/Structs/Direction.h>

#include <string>
#include <unordered_set>
#include <vector>
#include <utility>

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

		/** Store PendingToKill actors then remove them on next update */
		std::vector<Actor*> PendingToKillActors;
		static inline unsigned int PendingToKillActorsAddExtend = 16;

		/** Add actor to remove in next update */
		void ActorPendToKill(Actor* ActorToKill)
		{
			if (PendingToKillActors.size() % PendingToKillActorsAddExtend)  // extend vector
				PendingToKillActors.reserve(PendingToKillActors.size() + PendingToKillActorsAddExtend);

			ActorToKill->PendToKill();
			PendingToKillActors.emplace_back(ActorToKill);
		}

		/** delete actors is RemovedActors */
		inline void DeletePendingKillActors() 
		{ 
			for (auto& A : PendingToKillActors) delete A; 
			PendingToKillActors.clear(); 
		}

	protected:
		std::unordered_set <Actor*> Actors;

		GameMode* GM_Owner = nullptr;

	public: 
		Level();
		virtual ~Level();

		template<class T, class... Args>
		T* SpawnActorFromClass(const std::string& Name, const Vec2& Pos, Anchor Anchor, Args&&... args)
		{
			// create actor
			T* SpawnedActor = new T(Name, Pos, std::forward<Args>(args)...);

			// anchor pos offset and sweep position handle
			Vec2 PosOffseted = Pos - GetAnchorOffset(SpawnedActor->GetSize(), Anchor);
			bool bSweepPosition = SpawnedActor->IsCollisionDynamic();
			SpawnedActor->SetPosition(PosOffseted, bSweepPosition);

			// register actor on level
			SpawnedActor->LevelOwner = this;
			Actors.insert(SpawnedActor);

			// GAME_LOG(warn, "Spawned Actor: {}_{} {}", SpawnedActor->GetName(), SpawnedActor->GetId(), (void*)SpawnedActor);
			return SpawnedActor;
		}

		inline void RemoveActor(Actor* ActorToRemove);
		
		inline GameMode* GetGameMode() const { return GM_Owner; }

		/** Called in GameMode Start() */
		virtual void OnStart() {};
		virtual void OnEnd() {};

		/** Called in GameMode Update() each frame */
		virtual void OnTick(float DeltaTime) {}

		/** Get all actors in level of chosen class. Slow operation */
		template<class T>
		std::vector<Actor*> GetAllActorsOfClass()
		{
			std::vector<Actor*> OutActors;

			for (auto& Actor : Actors)
			{
				if (dynamic_cast<T*>(Actor)) OutActors.emplace_back(Actor);
			}
			return OutActors;
		}

		/** Get all actors in level of chosen class */
		template<class T> Actor* GetActorOfClass() 
		{
			for (auto& Actor : Actors)
			{
				if (dynamic_cast<T*>(Actor)) return Actor;
			}
			return nullptr;
		}

		/** Get first matched actor with accordant name */
		Actor* GetActorByName(const std::string& ActorName)
		{
			for (auto& Actor : Actors)
			{
				if (Actor->GetName() == ActorName) return Actor;
			}
			return nullptr;
		}

	};


}
