#include "TankiLevel_0.h"

#include <Game/Actors/TankActor.h>

namespace Game {

	TankiLevel_0::TankiLevel_0()
	{
		SpawnActorFromClass<Tank>("MyTank", VecInt2D(0, 440));
	}

	void TankiLevel_0::OnTick(float DeltaTime)
	{
	}

}