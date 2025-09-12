#include "LayerStack.h"

namespace Dunix
{
	void LayerStack::PushLayer(std::unique_ptr<Layer>inLayer)
	{
		inLayer->OnAttach();
	}

	void LayerStack::PushOverlay(std::unique_ptr<Layer>inOverlay)
	{
		m_Layers.emplace_back(inOverlay);
		inOverlay->OnAttach();
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