#include <PCH_Framework.h>
#include "Actor.h"

#include "Components/EntityComponent.h"

namespace Framework2D
{
	Actor::Actor(const std::string& Name, const VecInt2D& Position)
		: BaseEntity(Name, 0, Position)
	{
	}

	Actor::~Actor()
	{
		ForEachComp([](ActorComponent* C) {delete C; });
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
	
	inline void Actor::SetPosition(const VecInt2D& NewPos, bool bSweep)
	{
		BaseEntity::SetPosition(NewPos, bSweep);
		ForEachComp([&](ActorComponent* C) { if (C->GetType() == ActorComponentType::EntityComponent) {
				auto BaseEntityComp = static_cast<BaseEntityComponent*>(C);
				BaseEntityComp->OnActorPositionChange(NewPos);
			}});
	}
	
	inline void Actor::SetSize(const VecInt2D& NewSize, bool bTranslateToComponents)
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
	}
	
}
