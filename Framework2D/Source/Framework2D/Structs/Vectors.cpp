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

	const VecInt2D VecInt2D::VecZero = VecInt2D(0, 0);
	const VecInt2D VecInt2D::VecOne = VecInt2D(1, 1);
	const VecInt2D VecInt2D::VecLeft = VecInt2D(-1, 0);
	const VecInt2D VecInt2D::VecRight = VecInt2D(1, 0);
	const VecInt2D VecInt2D::VecUp = VecInt2D(0, -1);
	const VecInt2D VecInt2D::VecDown = VecInt2D(0, 1);
}
