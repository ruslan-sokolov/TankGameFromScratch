#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Framework2D/Graphic2D/Entities/BaseEntity.h>

namespace Framework2D {

	class Level;

	class FRAMEWORK2D_API Actor : private BaseEntity /* can be treated as base class */
	{
		friend class Level;

		// base entity components to translate position
		
		// set size , set pos, set color, set size internal, set pos internal

		// component iterator
		
		// get components by class
		// get component by name

		Level* LevelOwner = nullptr;

	public:
		virtual ~Actor();

		virtual void OnTick(float DeltaTime) = 0;

		inline Level* GetLevel() const { return LevelOwner; }

	protected:
		Actor(const std::string& Name, const VecInt2D& Position);  // can be spawned only through level instance;

	};
}
