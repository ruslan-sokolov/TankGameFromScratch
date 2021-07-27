#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	struct FRAMEWORK2D_API TimerHandle
	{
		friend struct TimerData;
		friend class SystemTimer;
		friend class LayerSystem;

	private:
		/** Represent index in SystemTimer::Timers */
		int TimerIndex;

	public:
		TimerHandle() : TimerIndex(-1) {}

		bool IsValid() const { return TimerIndex != -1; }
		void Invalidate() { TimerIndex = -1; }
	};

}
