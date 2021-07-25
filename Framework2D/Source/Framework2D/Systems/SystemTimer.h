#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <functional>
#include <vector>

namespace Framework2D
{
	class LayerSystem;
	class SystemTimer;
	struct TimerData;

	using TimerCbFn = std::function<void()>;

	struct TimerHandle
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

	struct TimerData
	{
		friend class SystemTimer;

		bool bLoop;
		float Rate;

		float TimeAcc;

		TimerHandle Handle;

		TimerCbFn Callback;

	private:
		void Update(float DeltaTime)
		{
			TimeAcc += DeltaTime;

			if (TimeAcc >= Rate)
			{
				Callback();

				if (bLoop)
					TimeAcc = 0;
				else
					Handle.Invalidate();
			}
		}

	public:
		TimerData() : bLoop(false), Rate(0), TimeAcc(0) {}
		TimerData(bool bLoop, float Rate, const TimerHandle& Handle, TimerCbFn&& Callback) 
			: bLoop(bLoop), Rate(Rate), TimeAcc(0), Handle(Handle), Callback(std::move(Callback)) {}

		// Movable only
		TimerData(TimerData&& Data) = default;
		TimerData(const TimerData& Data) = delete;
		TimerData& operator=(TimerData&&) = default;
		TimerData& operator=(const TimerData&) = delete;

	};

	constexpr int VecTimerDataExtend = 16;

	/*
	 * This system handles delayed function execution
	 */
	class FRAMEWORK2D_API SystemTimer
	{
		friend class LayerSystem;

		static std::vector<TimerData> Timers;

		static inline void AddTimer(TimerData&& Data);
		static inline void UpdateTimers(float DeltaTime);

	public:
		/** Use to remove timer if handle is valid */
		static inline void RemoveTimer(TimerHandle& Handle);
		/** use to set new timer, if handle is valid - remove existing timer first */
		static inline void SetTimer(TimerHandle& InOutHandle, TimerCbFn&& Callback, float Rate, bool bLoop = false);
	};

#define TIMER_CALLBACK(x) std::bind(&x, this) 
}


