#include <PCH_Framework.h>
#include "Vectors.h"

namespace Framework2D {

	const Vec4 Vec4::BlackColor = Vec4(0.f, 0.f, 0.f, 0.f);
	const Vec4 Vec4::WhiteColor = Vec4(1.f, 1.f, 1.f, 1.f);
	const Vec4 Vec4::RedColor = Vec4(1.f, 0.f, 0.f, 1.f);
	const Vec4 Vec4::GreenColor = Vec4(0.f, 1.f, 0.f, 1.f);
	const Vec4 Vec4::BlueColor = Vec4(0.f, 0.f, 1.f, 1.f);
	const Vec4 Vec4::YellowColor = Vec4(1.f, 1.f, 0.f, 1.f);
	const Vec4 Vec4::CyanColor = Vec4(0.f, 1.f, 1.f, 1.f);
	const Vec4 Vec4::MagentaColor = Vec4(1.f, 0.f, 1.f, 1.f);
	const Vec4 Vec4::GrayColor = Vec4(0.5f, 0.5f, 0.5f, 1.f); 

	const Vec2Int Vec2Int::VecZero = Vec2Int(0, 0);
	const Vec2Int Vec2Int::VecOne = Vec2Int(1, 1);
	const Vec2Int Vec2Int::VecLeft = Vec2Int(-1, 0);
	const Vec2Int Vec2Int::VecRight = Vec2Int(1, 0);
	const Vec2Int Vec2Int::VecUp = Vec2Int(0, -1);
	const Vec2Int Vec2Int::VecDown = Vec2Int(0, 1);

	const Vec2 Vec2::VecZero = Vec2(0.f, 0.f);
	const Vec2 Vec2::VecOne = Vec2(1.f, 1.f);
	const Vec2 Vec2::VecLeft = Vec2(-1.f, 0.f);
	const Vec2 Vec2::VecRight = Vec2(1.f, 0.f);
	const Vec2 Vec2::VecUp = Vec2(0.f, -1.f);
	const Vec2 Vec2::VecDown = Vec2(0.f, 1.f);
}
