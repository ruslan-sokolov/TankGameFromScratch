#include "PickupRespawnPointActor.h"

#include <Framework2D/Gameplay/Level.h>
#include <Framework2D/Gameplay/Game2D.h>
#include <Framework2D/Gameplay/Controllers/PlayerController.h>

#include <Game/Game.h>
#include <Game/Actors/Boosters/BoosterAddRespawnPointActor.h>

namespace Game {

	PickupRespawnPoint::PickupRespawnPoint(const std::string& Name, const Vec2& Position)
		: PickupBase(Name, Position, ResPath::T_BOOST_HP)
	{
	}

	bool PickupRespawnPoint::OnPick(Actor* Picker)
	{
		if (auto PC = GetPlayerController())
		{
			if (Picker && Picker == PC->GetControlledActor())
			{
				BoosterAddRespawnPoint::SpawnHPBoosterActivated(GetLevel(), Picker);
				return true;
			}
		}

		return false;
	}

	PickupRespawnPoint* PickupRespawnPoint::SpawnPickupRespawnPoint(Level* Level, const Vec2& Position)
	{
		ENGINE_ASSERT(Level, "PickupRespawnPoint::SpawnPickupHP(Level, Vec2 const&) Level is nullptr!");

		PickupRespawnPoint* Pickup = nullptr;
		
		if (Level) 
			Pickup = Level->SpawnActorFromClass<PickupRespawnPoint>("PickupRespawnPoint", Position, Anchor::CENTER);

		return Pickup;
	}
}
