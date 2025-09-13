#pragma once

#include "dxpch.h"
#include "Core.h"
#include "Layer.h"

namespace Dunix
{
	class DUNIX_API LayerStack
	{
	public:
		void PushLayer(Layer* inLayer);
		void PushOverlay(Layer* inOverlay);

	    void PopLayer(Layer* inLayer);
		void PopOverlay(Layer* inOverlay);

		void OnUpdate();
		void OnEvent(Event& e);

	private:
		std::vector<Layer*>m_Layers;

		size_t m_LastLayerIndex = 0; // [0..m_LastLayerIndex) = normal layers, [m_InsertIndex..end) = overlays
	};
}