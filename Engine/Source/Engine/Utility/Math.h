#pragma once

#include <Engine/Core.h>

#include <cmath>
#include <cstdlib>
#include <ctime>

#define PI              (3.1415926535897932f)
#define SMALL_NUMBER    (1.e-8f)

namespace Engine {

	// return float in range [0.f, 1.f]
	inline float RandFloat() { return ((float)std::rand()) / (float)RAND_MAX; }

	// return float in range [Min, Max]
	inline float RandFloatRange(float Min, float Max) { return Min + (Max - Min) * RandFloat(); }

	// return int in range [0, RAND_MAX]
	inline int RandInt() { return std::rand(); }

	// return int in range [0, Max)
	inline int RandIntMax(int Max) { return RandInt() % Max; }

	// return int in range [Min, Max)
	inline int RandIntRange(int Min, int Max) { return Min + (RandInt() % (Max - Min)); }

	// return cos
	inline float Cos(float Val) { return cosf(Val); }

	// return sin
	inline float Sin(float Val) { return sinf(Val); }

	// return tan
	inline float Tan(float Val) { return tanf(Val); }

	// return asin
	inline float Asin(float Val) { return asinf(Val); }

	// return acos
	inline float ACos(float Val) { return acosf(Val); }

	// return atan
	inline float ATan(float Val) { return atanf(Val); }

	constexpr float RadToDegCoef = 180.0f / PI;
	constexpr float DegToRadCoef = PI / 180.0f;

	inline float RadToDeg(float Radians) { return Radians * RadToDegCoef; }
	inline float DegToRad(float Degree) { return Degree * DegToRadCoef; }

	// return atan2(y,x)
	inline float Atan2(float X, float Y) { return atan2f(Y, X); }

	// return inverse square root
	inline float InvSqrt(float Val)
	{
		union {
			float f;
			unsigned int i;
		} conv;
		
		float x2;
		const float threehalfs = 1.5f;
		
		x2 = Val * 0.5f;
		
		conv.f = Val;
		conv.i = 0x5f3759df - (conv.i >> 1);
		conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
		
		return conv.f;
	}

	inline float Sqrt(float Val) { return sqrtf(Val); }
	inline float Abs(float Val) { return std::abs(Val); }
	inline float Pow(float X, float Y) { return std::powf(X, Y); }

	/** Returns 1, 0, or -1 depending on relation of T to 0 */
	template<class T>
	inline T Sign(const T A)
	{
		return (A > (T)0) ? (T)1 : ((A < (T)0) ? (T)-1 : (T)0);
	}
}
