#include "BoomActor.h"

#include <Framework2D/Gameplay/Level.h>

namespace Game {

	Boom::Boom(const std::string& Name, const Vec2& Position, std::initializer_list<const char*>BoomTexPathList, float AnimRate)
		: Actor(Name, Position)
	{
		auto SpriteBoom = EntityComponent<SpriteEntity>((Actor*)this, Name, Position, ResPath::T_BOOM_SMALL_0);


		//auto BoomComp = EntityComponent<SpriteSequence>((Actor*)this, Name, Position, AnimRate, BoomTexPathList);

		//auto BoomComp = EntityComponent<SpriteFlipFlop>((Actor*)this, Name, Position, AnimRate, ResPath::T_BOOM_BIG_0, ResPath::T_BOOM_BIG_1);
		//SetActorLifeTime(AnimRate * BoomTexPathList.size());

		// Initialize actor size
		//SetSize(BoomComp.GetSize());
	}

	Boom* Boom::SpawnBoomSmall(Level* Level, const Vec2& Position)
	{
		auto BoomSmall = Level->SpawnActorFromClass<Boom>("BoomSmall", Position, Anchor::CENTER,
			std::initializer_list{ ResPath::T_BOOM_SMALL_0, ResPath::T_BOOM_SMALL_1, ResPath::T_BOOM_SMALL_2 }, 
			GameConst::BOOM_SMALL_ANIM_SPEED);
		
		return BoomSmall;
	}

	Boom* Boom::SpawnBoomBig(Level* Level, const Vec2& Position)
	{
		auto BoomBig = Level->SpawnActorFromClass<Boom>("BoomBig", Position, Anchor::CENTER,
			std::initializer_list{ ResPath::T_BOOM_BIG_0, ResPath::T_BOOM_BIG_1, ResPath::T_BOOM_SMALL_0, ResPath::T_BOOM_SMALL_1, ResPath::T_BOOM_SMALL_2 },
			GameConst::BOOM_SMALL_ANIM_SPEED);

		return BoomBig;
	}


}