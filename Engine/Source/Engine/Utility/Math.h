#pragma once

#include <Engine/Core.h>

#include <cmath>

namespace Engine {

	inline float RandFloat() { return ((float)std::rand()) / (float) RAND_MAX; }

	inline float RandFloatRange(float Min, float Max) { return Min + (Max - Min) * RandFloat(); }

}
