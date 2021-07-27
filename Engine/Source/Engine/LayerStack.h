// Code in this file use source from and inspired by TheCherno/Hazel engine project
// https://github.com/TheCherno/Hazel/


#pragma once

#include <Engine/Layer.h>

#include <vector>

namespace Engine {

	class ENGINE_API LayerStack
	{
		std::vector<Layer*> Layers;
		std::vector<Layer*>::iterator LayerInsert;

	public:
		LayerStack() { LayerInsert = Layers.begin(); }
		~LayerStack() { for (Layer* layer : Layers) delete layer; }

		inline std::vector<Layer*>::iterator begin() { return Layers.begin(); }
		inline std::vector<Layer*>::iterator end() { return Layers.end(); }
		inline unsigned int Size() { return Layers.size(); }

		inline void PushLayer(Layer* layer) 
		{ 
			LayerInsert = Layers.emplace(LayerInsert, layer);
			layer->OnAttach();
		}
		
		inline void PushOverlay(Layer* overlay) 
		{ 
			Layers.emplace_back(overlay);
			overlay->OnAttach();
		}
		
		inline void PopLayer(Layer* layer)
		{
			std::vector<Layer*>::iterator it = std::find(Layers.begin(), Layers.end(), layer);
			if (it != Layers.end())
			{
				Layers.erase(it);
				--LayerInsert;
				(*it)->OnDetach();
			}
		}

		inline void PopOverlay(Layer* overlay)
		{
			std::vector<Layer*>::iterator it = std::find(Layers.begin(), Layers.end(), overlay);
			if (it != Layers.end()) 
			{
				Layers.erase(it);
				(*it)->OnDetach();
			}
		}

		inline Layer* GetLayer(Layer* layer)
		{
			std::vector<Layer*>::iterator it = std::find(Layers.begin(), Layers.end(), layer);
			if (it != Layers.end())
				return *it;
			else
				return nullptr;
		}

		inline Layer* GetLayer(const std::string& LayerName)
		{
			for (auto& layer : Layers)
			{
				if (layer->GetName() == LayerName)
					return layer;
			}
			return nullptr;
		}
	};

}
