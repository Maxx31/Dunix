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

		void PushLayer(Layer* inLayer);
		void PushOverlay(Layer* inOverlay);
	    void PopLayer(Layer* inLayer);
		void PopOverlay(Layer* inOverlay);

		void OnUpdate();
		void OnEvent(Event& e);

		auto begin() { return m_Layers.begin(); }
		auto end() { return m_Layers.end(); }

	private:
		std::vector<Layer*>m_Layers;

		size_t m_LastLayerIndex = 0; // [0..m_LastLayerIndex) = normal layers, [m_InsertIndex..end) = overlays
	};
}