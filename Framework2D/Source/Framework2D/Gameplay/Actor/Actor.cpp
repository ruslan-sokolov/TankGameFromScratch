#include <PCH_Framework.h>
#include "Actor.h"

#include "Components/EntityComponent.h"

#include <Framework2D/Gameplay/Level.h>

#include <Framework2D/Systems/SystemTimer.h>


namespace Framework2D
{	
	Actor::Actor(const std::string& Name, const Vec2& Position)
		: Id(TotalActorsCreatedNum), BaseEntity(Name, 0, Position)
	{
		++TotalActorsCreatedNum;
	}

	Actor::~Actor()
	{
		for (auto& Comp : Components)
		{
			delete Comp;
		}
	}

	void Actor::Update(float DeltaTime)
	{
		ForEachComp([=](ActorComponent* C) { if (C->IsCompTickEnabled()) C->OnCompTick(DeltaTime); });
		OnTick(DeltaTime);
	}
	
	inline std::vector<ActorComponent*> Actor::GetAllComponentsByType(ActorComponentType Type)
	{
		std::vector<ActorComponent*> OutComps;
		ForEachComp([&](ActorComponent* C) {if (C->GetType() == Type) OutComps.push_back(C); });
		return OutComps;
	}
	
	inline ActorComponent* Actor::GetComponentByType(ActorComponentType Type)
	{
		for (auto& Comp : Components) if (Comp->GetType() == Type) return Comp;
		return nullptr;
	}
	
	inline void Actor::SetEnableRender(bool bEnable)
	{
		ForEachComp([&](ActorComponent* C) { if (C->GetType() == ActorComponentType::EntityComponent) {
			auto BaseEntityComp = static_cast<BaseEntityComponent*>(C);
			if (auto Entity = BaseEntityComp->GetEntity())
				Entity->SetEnableRender(bEnable);
		}});

		BaseEntity::SetEnableRender(bEnable);
	}

	inline void Actor::SetPosition(const Vec2& NewPos, bool bSweep)
	{
		BaseEntity::SetPosition(NewPos, bSweep);
		ForEachComp([&](ActorComponent* C) { if (C->GetType() == ActorComponentType::EntityComponent) {
				auto BaseEntityComp = static_cast<BaseEntityComponent*>(C);
				BaseEntityComp->OnActorPositionChange(NewPos);
			}});
	}
	
	inline void Actor::SetSize(const Vec2& NewSize, bool bTranslateToComponents)
	{
		BaseEntity::SetSize(NewSize);
	
		if (bTranslateToComponents)
		{
			ForEachComp([&](ActorComponent* Comp) {if (Comp->GetType() == ActorComponentType::EntityComponent) {
				auto BaseEntityComp = static_cast<BaseEntityComponent*>(Comp);
				BaseEntityComp->SetSize(NewSize);
			}});
		}
	}
	
	inline void Actor::AddComponent(ActorComponent* Component)
	{
		Components.push_back(Component);

	}
	
	inline void Actor::RemoveComponent(ActorComponent* Component)
	{
		auto _findIf = [&](ActorComponent* Comp) {return Comp == Component; };
		Components.erase(std::remove_if(Components.begin(), Components.end(), _findIf));
		delete Component;
	}
	
	inline void Actor::SetActorLifeTime(float TimeToLive)
	{
		SystemTimer::SetTimer(TimerHandle_TimeToLive, TIMER_CALLBACK(Actor::Destroy), TimeToLive);
	}

	inline void Actor::PendToKill()
	{
		if (bIsPendingKill) return;

		SetEnableRender(false);

		SystemTimer::RemoveTimer(TimerHandle_TimeToLive);

		//DisableCollision();
		
		bIsPendingKill = true;
	}

	inline void Actor::Destroy()
	{
		LevelOwner->RemoveActor(this);
	}

}
