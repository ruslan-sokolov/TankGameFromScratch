#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D
{
	class BaseEntity;

	/*
	 * This system handles delayed function execution
	 */
	class FRAMEWORK2D_API SystemTimer
	{
	public:

		static void UpdateTimers(float DeltaTime);

	};
}


