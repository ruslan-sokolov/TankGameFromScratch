#pragma once

#include <Framework2D/Framework2DAPI.h>
#include <Engine.h>

#include <vector>

namespace Framework2D {

	/*
	 * this Engine Layer used for handle stuff like collision, delayed functions and input
	 */
	class FRAMEWORK2D_API LayerSystem : public Engine::Layer
	{

	public:
		LayerSystem(const std::string& LayerName);
		~LayerSystem();

		void OnUpdate(float DeltaTime) override;
		void OnEvent(Engine::Event& e) override;
	};

}