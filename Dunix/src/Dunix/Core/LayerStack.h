#pragma once
#include "Core.h"
#include "Layer.h"

namespace Dunix
{
	class DUNIX_API LayerStack
	{
	public:
		void PushLayer(std::unique_ptr<Layer>inLayer);
		void PushOverlay(std::unique_ptr<Layer>inOverlay);

		std::unique_ptr<Layer> PopLayer(Layer* inLayer);
		std::unique_ptr<Layer> PopOverlay(Layer* inOverlay);

	private:
		std::vector<std::unique_ptr<Layer>>m_Layers;

		size_t m_LastLayerIndex = 0; // [0..m_LastLayerIndex) = normal layers, [m_InsertIndex..end) = overlays
	};
}