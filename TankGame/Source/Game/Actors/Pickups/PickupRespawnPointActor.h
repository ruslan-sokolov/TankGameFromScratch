#pragma once

#include "PickupBaseActor.h"

namespace Game {

	class PickupRespawnPoint : public PickupBase
	{

	public:
		/*
		 * This class is represent pickup which on pick will activate boost which will increase player respawn number
		 */
		PickupRespawnPoint(const std::string& Name, const Vec2& Position);

		virtual bool OnPick(Actor* Picker) override;

		static PickupRespawnPoint* SpawnPickupRespawnPoint(Level* Level, const Vec2& Position);
	};

}
