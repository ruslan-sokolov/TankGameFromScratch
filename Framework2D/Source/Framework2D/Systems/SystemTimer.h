#pragma once

#include <Framework2D/Framework2DAPI.h>

#include <Framework2D/Structs/TimerHandle.h>

#include <functional>
#include <vector>

namespace Framework2D
{
	class LayerSystem;
	class SystemTimer;
	struct TimerData;

	using TimerCbFn = std::function<void()>;

	struct TimerData
	{
		friend class SystemTimer;

		bool bLoop;
		float Rate;

		float ExpireTime;

		TimerHandle Handle;

		TimerCbFn Callback;

	private:
		void Update(float DeltaTime)
		{
			if (Handle.IsValid())
			{
				ExpireTime -= DeltaTime;

				if (ExpireTime <= 0.f)
				{
					Callback();

					if (bLoop)
						ExpireTime = Rate;
					else
					{

						Handle.Invalidate();
					}
				}
			}
		}

	public:
		TimerData() : bLoop(false), Rate(0), ExpireTime(0) {}
		TimerData(bool bLoop, float Rate, float ExpireTime, const TimerHandle& Handle, TimerCbFn&& Callback) 
			: bLoop(bLoop), Rate(Rate), ExpireTime(ExpireTime), Handle(Handle), Callback(std::move(Callback)) {}

		// Movable only
		TimerData(TimerData&& Data) = default;
		TimerData(const TimerData& Data) = delete;
		TimerData& operator=(TimerData&&) = default;
		TimerData& operator=(const TimerData&) = delete;

	};

	constexpr int VecTimerDataExtend = 16;

	/*
	 * This system handles delayed function execution
	 * It's stable to add/remnove timer in timer callback function
	 */
	class FRAMEWORK2D_API SystemTimer
	{
		friend class LayerSystem;

		static inline int TotalCreatedNum = 0; // this will be unique timer identifier
		static std::vector<TimerData> Timers;

		/** This is allow as to add timer in delayed timer function execution while iteration all timers */
		static std::vector<TimerData> TimersPushbackQueue;

		static inline TimerData* FindTimer(const TimerHandle& InHandle);
		
		/* Put new created timer in TimersPushbackQueue */
		static inline void AddTimer(TimerData&& Data);
		/** Insert TimersPushbackQueue in Timers queue to activate them */
		static inline void InsertNewTimers();
		/** Main timers loop, will increment each timer time and execute them if timer elapsed */
		static inline void UpdateTimers(float DeltaTime);

	public:
		/** Use to remove timer if handle is valid */
		static inline void RemoveTimer(TimerHandle& InOutHandle);
		/** use to set new timer, if handle is valid - remove existing timer first */
		static inline void SetTimer(TimerHandle& InOutHandle, TimerCbFn&& InCallback, float InRate, bool InbLoop = false, float InFirstDelay = -1.f);
		/** Uste to remove all timers, on level change for e.g. */
		static inline void RemoveAllTimers();
	};

#define TIMER_CALLBACK(x) std::bind(&x, this) 
}
