#pragma once
#include <Framework2D/Framework2DAPI.h>

#include <Framework2D/Structs/Vectors.h>
#include <string>
#include <unordered_set>

namespace Framework2D {	
	class Actor;
	class GameMode;

	class FRAMEWORK2D_API Level
	{
		friend class GameMode;

		std::unordered_set <Actor*> Actors;

		GameMode* GM_Owner;

	public: 
		virtual ~Level();

		template<typename T>
		inline T* SpawnActorFromClass(const std::string& Name, const VecInt2D& Pos);

		inline void RemoveActor(Actor* ActorToRemove);
		
		inline GameMode* GetGameMode() const { return GM_Owner; }

		// todo: get actors of class
		// todo: get actor by name

	protected:

		Level(GameMode* GM_Owner);

	};


}
