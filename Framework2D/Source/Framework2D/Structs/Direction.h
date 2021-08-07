#pragma once

#include "Vectors.h"

namespace Framework2D {

	enum class FRAMEWORK2D_API Direction
	{
		LEFT,
		RIGHT,
		DOWN,
		UP
	};

	// ------------------------------------------------------------------ //

	inline Direction GetRandomDirection()
	{
		return static_cast<Direction>(std::rand() % 4);
	}

	// return new random direction not equal to DirToIgnore
	inline Direction GetRandDirectionFilter(Direction DirToIgnore)
	{
		Direction NewDirection = DirToIgnore;
		while (NewDirection == DirToIgnore)
			NewDirection = GetRandomDirection();

		return NewDirection;
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

	// ------------------------------------------------------------------ //

	inline Direction GetDirection(const Vec2Int& DeltaVec)
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

	inline Direction GetDirection(const Vec2& DeltaVec)
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

	inline Direction GetDirection(const Vec2Int& From, const Vec2Int& To)
	{
		return GetDirection(From - To);
	}

	inline Direction GetDirection(const Vec2& From, const Vec2& To)
	{
		return GetDirection(From - To);
	}

	// ------------------------------------------------------------------ //

	inline Vec2Int DirectionToVec2Int(Direction Dir)
	{
		Vec2Int DirectionVector;

		switch (Dir)
		{
		case Direction::UP:
			DirectionVector = Vec2Int::VecUp;
			break;
		case Direction::DOWN:
			DirectionVector = Vec2Int::VecDown;
			break;
		case Direction::LEFT:
			DirectionVector = Vec2Int::VecLeft;
			break;
		default:
			DirectionVector = Vec2Int::VecRight;
			break;
		}

		return DirectionVector;
	}

	inline Vec2Int GetDirectionVec2Int(const Vec2Int& DeltaVec)
	{
		return DirectionToVec2Int(GetDirection(DeltaVec));
	}

	inline Vec2Int GetDirectionVec2Int(const Vec2Int& From, const Vec2Int& To)
	{
		return DirectionToVec2Int(GetDirection(From - To));
	}

	// ------------------------------------------------------------------ //

	inline Vec2 DirectionToVec2(Direction Dir)
	{
		Vec2 DirectionVector;

		switch (Dir)
		{
		case Direction::UP:
			DirectionVector = Vec2::VecUp;
			break;
		case Direction::DOWN:
			DirectionVector = Vec2::VecDown;
			break;
		case Direction::LEFT:
			DirectionVector = Vec2::VecLeft;
			break;
		default:
			DirectionVector = Vec2::VecRight;
			break;
		}

		return DirectionVector;
	}

	inline Vec2 GetDirectionVec2(const Vec2& DeltaVec)
	{
		return DirectionToVec2(GetDirection(DeltaVec));
	}

	inline Vec2Int GetDirectionVec2(const Vec2Int& From, const Vec2Int& To)
	{
		return DirectionToVec2(GetDirection(From - To));
	}

	// ------------------------------------------------------------------ //
}
