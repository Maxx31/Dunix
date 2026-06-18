#pragma once

#include "dxpch.h"
#include "Core.h"
#include "Layer.h"

namespace Dunix
{
	class DUNIX_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		template <typename T , class ...Args>
		T* PushLayer(Args&&... args)
		{
			static_assert(std::is_base_of_v<Layer, T>, "T must derive from Layer");
			
			auto layer = std::make_unique<T>(std::forward<Args>(args)...);
			auto layerPtr = layer.get();
			
			auto pos = m_Layers.begin() + m_LastLayerIndex;
			m_Layers.insert(pos, std::move(layer));
			m_LastLayerIndex++;
			
			layerPtr->OnAttach();
			return layerPtr;
		} 
		
		template <typename T , class ...Args>
		T* PushOverlay(Args&&... args)
		{
			static_assert(std::is_base_of_v<Layer, T>, "T must derive from Layer");
			
			auto layer = std::make_unique<T>(std::forward<Args>(args)...);
			auto layerPtr = layer.get();
			
			m_Layers.push_back(std::move(layer));
			
			layerPtr->OnAttach();
			return layerPtr;
		} 
		
	    void PopLayer(Layer* inLayer);
		void PopOverlay(Layer* inOverlay);

		void OnUpdate(class Timestep ts);
		void OnEvent(Event& e);

		auto begin() { return m_Layers.begin(); }
		auto end() { return m_Layers.end(); }

	private:
		std::vector<std::unique_ptr<Layer>>m_Layers;
		
		int m_LastLayerIndex = 0;	// [0..m_LastLayerIndex) = normal layers
									// [m_LastLayerIndex..end) = overlays
	};
}
