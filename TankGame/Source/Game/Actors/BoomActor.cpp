#include "BoomActor.h"

#include <Game/Game.h>
#include <Framework2D/Gameplay/Level.h>
#include <Framework2D/Gameplay/Actor/Components/EntityComponent.h>

namespace Game {

	Boom::Boom(const std::string& Name, const Vec2& Position, std::initializer_list<const char*>BoomTexPathList, float AnimRate)
		: Actor(Name, Position)
	{
		auto BoomComp = new EntityComponent<SpriteSequence>((Actor*)this, Name, Position, AnimRate, BoomTexPathList);

		SetActorLifeTime(AnimRate * BoomTexPathList.size());

		// Initialize actor size
		SetSize(BoomComp->GetSize());
 	}

	Boom* Boom::SpawnBoomSmall(Level* Level, const Vec2& Position)
	{
		auto BoomSmall = Level->SpawnActorFromClass<Boom>("BoomSmall" + std::to_string(GetTotalActorsCreatedNum()), Position, Anchor::CENTER,
			std::initializer_list{ ResPath::T_BOOM_SMALL_0, ResPath::T_BOOM_SMALL_1, ResPath::T_BOOM_SMALL_2 }, 
			GameConst::BOOM_SMALL_ANIM_SPEED);
		
		return BoomSmall;
	}

	Boom* Boom::SpawnBoomBig(Level* Level, const Vec2& Position)
	{
		auto BoomBig = Level->SpawnActorFromClass<Boom>("BoomBig" + std::to_string(GetTotalActorsCreatedNum()), Position, Anchor::CENTER,
			std::initializer_list{ResPath::T_BOOM_SMALL_0, ResPath::T_BOOM_SMALL_1, ResPath::T_BOOM_SMALL_2, ResPath::T_BOOM_BIG_0, ResPath::T_BOOM_BIG_1 },
			GameConst::BOOM_SMALL_ANIM_SPEED);

		return BoomBig;
	}


}