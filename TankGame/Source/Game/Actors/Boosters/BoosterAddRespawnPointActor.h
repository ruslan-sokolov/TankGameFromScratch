#pragma once

#include "BoosterBaseActor.h"

namespace Game
{

	class BoosterAddRespawnPoint : public BoosterBase
	{
	public:
		/*
		 * This class is represent booster, which applying momentanly and increase player respawn num
		 */
		BoosterAddRespawnPoint(const std::string Name, const Vec2& Position);

		virtual void OnActivated(Actor* Activator) override;

		static BoosterAddRespawnPoint* SpawnHPBoosterActivated(Level* Level, Actor* Activator);
	};

}