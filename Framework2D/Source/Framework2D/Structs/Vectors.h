#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <Engine/Utility/Math.h>

#include <cmath>

#include <iostream>
#include <string>
#include <sstream>


namespace Framework2D {

	struct Vec2Int;

	struct FRAMEWORK2D_API Vec4
	{
		float R, G, B, A;
		Vec4() : R(0), G(0), B(0), A(0) {}
		Vec4(float R, float G, float B, float A) : R(R), G(G), B(B), A(A) {}

		std::string ToString() const { std::stringstream SS; SS << "R=" << R << ", G=" << G << ", B=" << B << ", A=" << A; return SS.str(); }

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
		Vec2(const Vec2Int&);

		inline bool operator == (const Vec2& Other) const { return X == Other.X && Y == Other.Y; }
		inline bool operator != (const Vec2& Other) const { return X != Other.X || Y != Other.Y; }

		inline Vec2 operator += (const Vec2& Other) { X += Other.X; Y += Other.Y; return *this; }
		inline Vec2 operator -= (const Vec2& Other) { X -= Other.X; Y -= Other.Y; return *this; }

		inline Vec2 operator + (const Vec2& Other) const { return Vec2(X + Other.X, Y + Other.Y); }
		inline Vec2 operator - (const Vec2& Other) const { return Vec2(X - Other.X, Y - Other.Y); }

		inline Vec2 operator - () const { return Vec2(-X, -Y); }

		inline Vec2 operator * (float Scalar) const { return Vec2(X * Scalar, Y * Scalar); }
		inline Vec2 operator * (const Vec2& Other) const { return Vec2(X * Other.X, Y * Other.Y); }
		inline Vec2 operator / (float Scalar) const { return Vec2(X / Scalar, Y / Scalar); }
		inline Vec2 operator / (const Vec2& Other) const { return Vec2(X / Other.X, Y / Other.Y); }

		inline Vec2 operator = (const Vec2& Other) { X = Other.X; Y = Other.Y; return *this; }

		inline bool NotEqualZero() { return X != 0 && Y != 0; }

		inline Vec2 GetAbs() const { return Vec2(std::abs(X), std::abs(Y)); }

		inline float Square() const { return X * Y; }

		inline float Size() const { return sqrt(X * X + Y * Y); }

		/** Creates new vector with smallest X and Y values of two vectors */
		inline static Vec2 GetMin(const Vec2& Left, const Vec2& Right)
		{
			return Vec2(Left.X < Right.X ? Left.X : Right.X, Left.Y < Right.Y ? Left.Y : Right.Y);
		}

		/** Creates new vector with biggest X and Y values of two vectors */
		inline static Vec2 GetMax(const Vec2& Left, const Vec2& Right) {
			return Vec2(Left.X > Right.X ? Left.X : Right.X, Left.Y > Right.Y ? Left.Y : Right.Y);
		}

		/** Returns dot product of two vectors */
		inline static float Dot(const Vec2& Left, const Vec2& Right) 
		{
			return Left.X * Right.X + Left.Y * Right.Y;
		}

		/** Returns cross product of two vectors (z component) */
		inline static float Cross(const Vec2& Left, const Vec2& Right) 
		{
			return Left.X * Right.Y - Left.Y * Right.X;
		}

		/** Normailize this vector */
		inline void Normalize(float Tolerance = SMALL_NUMBER)
		{
			const float SquareSum = X * X + Y * Y;
			if (SquareSum > Tolerance)
			{
				const float Scale = Engine::InvSqrt(SquareSum);
				X *= Scale;
				Y *= Scale;
				return;
			}
			X = 0.0f;
			Y = 0.0f;
		}

		/** Get normalized copy of vector */
		inline Vec2 GetNormalized() const { Vec2 Copy(X, Y); Copy.Normalize(); return Copy; }

		static const Vec2 VecZero;
		static const Vec2 VecOne;
		static const Vec2 VecLeft;
		static const Vec2 VecRight;
		static const Vec2 VecUp;
		static const Vec2 VecDown;

		std::string ToString() const { std::stringstream SS; SS << "X=" << X << ", Y=" << Y; return SS.str(); }
	};

	struct FRAMEWORK2D_API Vec2Int
	{
	public:
		int X = 0;
		int Y = 0;

		Vec2Int() {}
		Vec2Int(const Vec2Int& Other) : X(Other.X), Y(Other.Y) {}
		Vec2Int(const Vec2& Other) : X(static_cast<int>(Other.X)), Y(static_cast<int>(Other.Y)) {};
		Vec2Int(int InX, int InY) : X(InX), Y(InY) {}
		Vec2Int(int InBoth) : X(InBoth), Y(InBoth) {}

		inline bool operator == (const Vec2Int& Other) const { return X == Other.X && Y == Other.Y; }
		inline bool operator != (const Vec2Int& Other) const { return X != Other.X || Y != Other.Y; }

		inline Vec2Int operator += (const Vec2Int& Other) { X += Other.X; Y += Other.Y; return *this; }
		inline Vec2Int operator -= (const Vec2Int& Other) { X -= Other.X; Y -= Other.Y; return *this; }

		inline Vec2Int operator + (const Vec2Int& Other) const { return Vec2Int(X + Other.X, Y + Other.Y); }
		inline Vec2Int operator - (const Vec2Int& Other) const { return Vec2Int(X - Other.X, Y - Other.Y); }

		inline Vec2Int operator - () const { return Vec2Int(-X, -Y); }

		inline Vec2Int operator * (int Scalar) const { return Vec2Int(X * Scalar, Y * Scalar); }
		inline Vec2Int operator / (int Scalar) const { return Vec2Int(X / Scalar, Y / Scalar); }

		inline Vec2Int operator = (const Vec2Int& Other) { X = Other.X; Y = Other.Y; return *this; }

		inline Vec2Int GetAbs() const { return Vec2Int(std::abs(X), std::abs(Y)); }

		inline int Square() const { return X * Y; }

		inline int Size() const { return sqrt(X * X + Y * Y); }

		/** Creates new vector with smallest X and Y values of two vectors */
		inline static Vec2Int GetMin(const Vec2Int& Left, const Vec2Int& Right)
		{
			return Vec2Int(Left.X < Right.X ? Left.X : Right.X, Left.Y < Right.Y ? Left.Y : Right.Y);
		}

		/** Creates new vector with biggest X and Y values of two vectors */
		inline static Vec2Int GetMax(const Vec2Int& Left, const Vec2Int& Right) {
			return Vec2Int(Left.X > Right.X ? Left.X : Right.X, Left.Y > Right.Y ? Left.Y : Right.Y);
		}

		static const Vec2Int VecZero;
		static const Vec2Int VecOne;
		static const Vec2Int VecLeft;
		static const Vec2Int VecRight;
		static const Vec2Int VecUp;
		static const Vec2Int VecDown;

		std::string ToString() const { std::stringstream SS; SS << "X=" << X << ", Y=" << Y; return SS.str(); }
	};

	inline Vec2::Vec2(const Vec2Int& Other) : X(Other.X), Y(Other.Y) {}

	inline std::ostream& operator << (std::ostream& os, const Vec2& v)
	{
		return os << v.ToString();
	}
	
	inline std::ostream& operator << (std::ostream& os, const Vec2Int& v)
	{
		return os << v.ToString();
	}

	inline std::ostream& operator << (std::ostream& os, const Vec4& v)
	{
		return os << v.ToString();
	}
}
