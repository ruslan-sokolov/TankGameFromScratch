#include "BoosterAddRespawnPointActor.h"

#include "Framework2D/Gameplay/Controllers/PlayerController.h"
#include <Framework2D/Gameplay/Level.h>


#include "Game/Game.h"
#include "Game/Gameplay/TankiGameMode.h"

namespace Game {

	BoosterAddRespawnPoint::BoosterAddRespawnPoint(const std::string Name, const Vec2& Position)
		: BoosterBase(Name, Position, 0)
	{
	}

	void BoosterAddRespawnPoint::OnActivated(Actor* Activator)
	{
		if (auto PC = GetPlayerController(); PC->GetControlledActor() == Activator)
		{
			if (auto GM = dynamic_cast<TankiGameMode*>(GetGM()))
			{
				GM->AddRespawnPoint(GameConst::BOOSTER_ADD_RESPAWN_POINT_NUM);
			}
		}
	}

	BoosterAddRespawnPoint* BoosterAddRespawnPoint::SpawnHPBoosterActivated(Level* Level, Actor* Activator)
	{
		ENGINE_ASSERT(Level, "BoosterAddRespawnPoint::SpawnHPBoosterActivated(..) level is nullptr!");

		if (Level)
		{
			auto BoosterRP = Level->SpawnActorFromClass<BoosterAddRespawnPoint>("BoosterAddRespawnPoint", 0, (Anchor)0);
			BoosterRP->ActivateBoost(Activator);
			return BoosterRP;
		}

		return nullptr;
	}

}
