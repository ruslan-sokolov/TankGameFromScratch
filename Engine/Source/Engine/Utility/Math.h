#pragma once

#include <Engine/Core.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

namespace Engine {

	// return float in range [0.f, 1.f]
	inline float RandFloat() { return ((float)std::rand()) / (float) RAND_MAX; }

	// return float in range [Min, Max]
	inline float RandFloatRange(float Min, float Max) { return Min + (Max - Min) * RandFloat(); }

	// return int in range [0, RAND_MAX]
	inline int RandInt() { return std::rand(); }

	// return int in range [0, Max)
	inline int RandIntMax(int Max) { return RandInt() % Max; }
	
	// return int in range [Min, Max)
	inline int RandIntRange(int Min, int Max) { return Min + (RandInt() % (Max - Min)); }
}
