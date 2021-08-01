#pragma once

#include <Framework2D/Framework2DAPI.h>

namespace Framework2D {

	struct FRAMEWORK2D_API TimerHandle
	{
		friend struct TimerData;
		friend class SystemTimer;
		friend class LayerSystem;

	private:
		/** Represent unique identifier in SystemTimer::Timers container */
		int TimerId;

		/* Use SystemTimer::RemoveTimer to remove timer */
		void Invalidate() { TimerId = -1; }

	public:
		TimerHandle() : TimerId(-1) {}

		bool IsValid() const { return TimerId != -1; }

		int GetTimerId() const { return TimerId; }

		bool operator==(const TimerHandle& Other) const { return TimerId == Other.TimerId; }
	};

}
