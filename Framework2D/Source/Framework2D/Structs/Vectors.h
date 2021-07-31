#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <cmath>

namespace Framework2D {

	struct VecInt2D;

	struct FRAMEWORK2D_API Vec4
	{
		float R, G, B, A;
		Vec4() : R(0), G(0), B(0), A(0) {}
		Vec4(float R, float G, float B, float A) : R(A), G(G), B(B), A(A) {}

		static const Vec4 BlackColor;
		static const Vec4 WhiteColor;
		static const Vec4 RedColor;
		static const Vec4 GreenColor;
		static const Vec4 BlueColor;
		static const Vec4 YellowColor;
		static const Vec4 CyanColor;
		static const Vec4 MagentaColor;
		static const Vec4 GrayColor;
	};

	struct FRAMEWORK2D_API Vec3
	{
		float X = 0;
		float Y = 0; 
		float Z = 0;
	};

	struct FRAMEWORK2D_API Vec2
	{
		float X = 0;
		float Y = 0;
		
		Vec2() : X(0), Y(0) {}
		Vec2(float X, float Y) : X(X), Y(Y) {}
		Vec2(int X, int Y) : X(X), Y(Y) {}
		Vec2(float Both) : X(Both), Y(Both) {}
		Vec2(const VecInt2D&);
	};

	struct FRAMEWORK2D_API VecInt2D
	{
	public:
		int X = 0;
		int Y = 0;

		VecInt2D() {}

		VecInt2D(const VecInt2D& Other) : X(Other.X), Y(Other.Y) {}
		 
		VecInt2D(const Vec2& Other) : X(static_cast<int>(Other.X)), Y(static_cast<int>(Other.Y)) {};

		VecInt2D(int InX, int InY) : X(InX), Y(InY) {}
		VecInt2D(int InBoth) : X(InBoth), Y(InBoth) {}

		inline bool operator == (const VecInt2D& Other) const { return X == Other.X && Y == Other.Y; }
		inline bool operator != (const VecInt2D& Other) const { return X != Other.X || Y != Other.Y; }

		inline VecInt2D operator += (const VecInt2D& Other) { X += Other.X; Y += Other.Y; return *this; }
		inline VecInt2D operator -= (const VecInt2D& Other) { X -= Other.X; Y -= Other.Y; return *this; }

		inline VecInt2D operator + (const VecInt2D& Other) const { return VecInt2D(X + Other.X, Y + Other.Y); }
		inline VecInt2D operator - (const VecInt2D& Other) const { return VecInt2D(X - Other.X, Y - Other.Y); }

		inline VecInt2D operator - () const { return VecInt2D(-X, -Y); }

		inline VecInt2D operator * (int Scalar) const { return VecInt2D(X * Scalar, Y * Scalar); }
		inline VecInt2D operator / (int Scalar) const { return VecInt2D(X / Scalar, Y / Scalar); }

		inline VecInt2D operator = (const VecInt2D& Other) { X = Other.X; Y = Other.Y; return *this; }

		inline VecInt2D GetAbs() const { return VecInt2D(std::abs(X), std::abs(Y)); }

		inline int Square() const { return X * Y; }

		inline int Size() const {
			int X_Square = X * X;
			int Y_Square = Y * Y;
			int Sum = X_Square + Y_Square;
			return sqrt(Sum);
		}

		/** Creates new vector with biggest X and Y values of two vectors */
		inline static VecInt2D GetMax(const VecInt2D& Vec1, const VecInt2D& Vec2) {
			return VecInt2D(Vec1.X > Vec2.X ? Vec1.X : Vec2.X, Vec1.Y > Vec2.Y ? Vec1.Y : Vec2.Y);
		}

		static const VecInt2D VecZero;
		static const VecInt2D VecOne;
		static const VecInt2D VecLeft;
		static const VecInt2D VecRight;
		static const VecInt2D VecUp;
		static const VecInt2D VecDown;
	};

	inline Vec2::Vec2(const VecInt2D& Other) : X(Other.X), Y(Other.Y) {}

	enum class FRAMEWORK2D_API Direction
	{
		LEFT,
		RIGHT,
		DOWN,
		UP
	};

	inline Direction GetRandomDirection()
	{
		return static_cast<Direction>(std::rand() % 4);
	}

	// fix this
	inline Direction GetDirection(VecInt2D DeltaVec)
	{
		if (DeltaVec.X - DeltaVec.Y > 0)
		{
			if (std::abs(DeltaVec.X) > std::abs(DeltaVec.Y))
			{
				return Direction::RIGHT;
			}
			else
			{
				return Direction::UP;
			}
		}
		else
		{
			if (std::abs(DeltaVec.X) > std::abs(DeltaVec.Y))
			{
				return Direction::LEFT;
			}
			else
			{
				return Direction::DOWN;
			}
		}
	}

	inline Direction GetDirection(VecInt2D From, VecInt2D To)
	{
		return GetDirection(From - To);
	}

	inline Direction GetDirectionOposite(Direction Dir)
	{
		Direction Oposite;

		switch (Dir)
		{
		case Direction::UP:
			Oposite = Direction::DOWN;
			break;
		case Direction::DOWN:
			Oposite = Direction::UP;
			break;
		case Direction::LEFT:
			Oposite = Direction::RIGHT;
			break;
		default:
			Oposite = Direction::LEFT;
			break;
		}

		return Oposite;
	}

	inline VecInt2D DirectionToVec(Direction Dir)
	{
		VecInt2D DirectionVector;

		switch (Dir)
		{
		case Direction::UP:
			DirectionVector = VecInt2D::VecUp;
			break;
		case Direction::DOWN:
			DirectionVector = VecInt2D::VecDown;
			break;
		case Direction::LEFT:
			DirectionVector = VecInt2D::VecLeft;
			break;
		default:
			DirectionVector = VecInt2D::VecRight;
			break;
		}

		return DirectionVector;
	}

	inline VecInt2D GetDirectionVector(VecInt2D DeltaVec)
	{
		return DirectionToVec(GetDirection(DeltaVec));
	}

	inline VecInt2D GetDirectionVector(VecInt2D From, VecInt2D To)
	{
		return DirectionToVec(GetDirection(From - To));
	}

	inline const char* DirectionToString(Direction Dir)
	{
		switch (Dir)
		{
		case Direction::LEFT:
			return "LEFT";
		case Direction::RIGHT:
			return "RIGHT";
		case Direction::UP:
			return "UP";
		default:
			return "DOWN";
		}
	}
}
