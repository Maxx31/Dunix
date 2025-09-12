#include "LayerStack.h"

namespace Dunix
{
	void LayerStack::PushLayer(std::unique_ptr<Layer>inLayer)
	{
		Layer* ptr = inLayer.get();
		m_Layers.insert(m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LastLayerIndex),
			std::move(inLayer));

		m_LastLayerIndex++;
		ptr->OnAttach();
	}

	void LayerStack::PushOverlay(std::unique_ptr<Layer>inOverlay)
	{
		Layer* ptr = inOverlay.get();
		m_Layers.emplace_back(std::move(inOverlay));
		ptr->OnAttach();
	}

	std::unique_ptr<Layer> LayerStack::PopLayer(Layer* inLayer)
	{
		return std::unique_ptr<Layer>();
	}

	std::unique_ptr<Layer> LayerStack::PopOverlay(Layer* inOverlay)
	{
		return std::unique_ptr<Layer>();
	}
}