#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Framework2D/Graphic2D/Entities/BaseEntity.h>
#include <Framework2D/Structs/TimerHandle.h>
#include "Components/ActorComponent.h"

namespace Framework2D {

	class ActorComponent;
	enum class ActorComponentType;
	class Level;

	class FRAMEWORK2D_API Actor : public BaseEntity
	{
		friend class Level;
		friend class ActorComponent;

		// Should be called in :evel, calls tick for actor and actor components;
		inline void Update(float DeltaTime);

		// Hide baseEntity update
		void OnUpdate(float DeltaTime) final {};

		std::vector<ActorComponent*> Components;

		Level* LevelOwner = nullptr;

		static inline unsigned int TotalActorsCreatedNum = 0;
		unsigned int Id;  // creation count num

		bool bIsPendingKill = false;

		/** Called in Level to add it to remove queue*/
		inline void PendToKill();

		TimerHandle TimerHandle_TimeToLive;

	public:
		// Call actor delayed destroy
		inline void SetActorLifeTime(float TimeToLive);

		bool IsPendingKill() const { return bIsPendingKill; }
		inline void Destroy();

		virtual ~Actor();

		/*
		 * Custom frame per frame actor logic
		 */
		virtual void OnTick(float DeltaTime) {}
		virtual void OnCollide(BaseEntity* Other, CollisionFilter Filter) {}

		inline Level* GetLevel() const { return LevelOwner; }
		inline static unsigned int GetTotalActorsCreatedNum() { return TotalActorsCreatedNum; }
		inline unsigned int GetId() const { return Id; }

		/** slow operation. runtime check for component class */
		template<class T>
		inline std::vector<T*> GetAllComponentsByClass()
		{
			std::vector<T*> OutComponents;
			
			auto _addComp = [&](ActorComponent* Comp) { if (auto T_Comp = dynamic_cast<T*>(Comp)) OutComponents.push_back(T_Comp); };
			ForEachComp(_addComp);
		
			return OutComponents;
		}
		
		/** slow operation. runtime check for component class and return first matched */
		template<class T>
		inline T* GetComponentByClass()
		{
			for (auto& Comp : Components) if (auto T_Comp = dynamic_cast<T*>(Comp)) return T_Comp;
			return nullptr;
		}
		
		inline std::vector<ActorComponent*> GetAllComponentsByType(ActorComponentType Type);
		inline ActorComponent* GetComponentByType(ActorComponentType Type);
		
		/*
		 * Hides BaseEntity implementation
		 * Set Actor Render Enable (will update all base entity components render enable)
		 */
		inline void SetEnableRender(bool bEnable);

		/* 
		 * Hides BaseEntity implementation
		 * Set Actor Position (will update all components relative pos) 
		 */
		inline void SetPosition(const Vec2& NewPos, bool bSweep = false);
		
		/* 
		 * Hides BaseEntity implementation
		 * Resize Actor if flag is true - translate new size to all EntityComponents 
		 */
		inline void SetSize(const Vec2& NewSize, bool bTranslateToComponents = false);

		// Remove component 
		inline void RemoveComponent(ActorComponent* Component);

	protected:
		//  Will be called from component constructor
		inline void AddComponent(ActorComponent* Component);
		
		/*
		 * Iterate Components with lambda function call for each
		 */
		template <class _Fn>
		inline void ForEachComp(const _Fn& Lambda) noexcept
		{
			std::for_each(Components.begin(), Components.end(), Lambda);
		}

	protected:
		Actor(const std::string& Name, const Vec2& Position);  // can be created only as derrived and from Level::SpawnActorFromClass();

	};
}
