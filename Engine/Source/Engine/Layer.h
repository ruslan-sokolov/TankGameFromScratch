// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

#include <Engine/Events/Event.h>

namespace Engine
{

	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& Name = "Layer")
			: Name(Name) {}

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float DeltaTime) {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return Name; }
	
	protected:
		std::string Name;
	};

}
