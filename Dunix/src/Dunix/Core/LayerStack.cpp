#include "dxpch.h"
#include "LayerStack.h"

#include "Dunix/Core/Timestep.h"

namespace Dunix
{
	LayerStack::LayerStack()
	{
		m_Layers.reserve(16);
	}

	LayerStack::~LayerStack()
	{
		for (auto& layer : m_Layers)
			layer->OnDetach();
	}

	void LayerStack::PopLayer(Layer* inLayer)
	{
		auto endIt = m_Layers.begin() + m_LastLayerIndex;
		auto res = std::find_if(m_Layers.begin(), endIt, [inLayer](const std::unique_ptr<Layer> & current)
		{
			return current.get() == inLayer;
		});

		if (res != endIt)
		{
			(*res)->OnDetach();
			m_Layers.erase(res);
			m_LastLayerIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* inOverlay)
	{
		auto beginIt = m_Layers.begin() + m_LastLayerIndex;

		auto res = std::find_if(beginIt, m_Layers.end(),
			[inOverlay](const std::unique_ptr<Layer>& current)
			{
				return current.get() == inOverlay;
			});

		if (res != m_Layers.end())
		{
			(*res)->OnDetach();
			m_Layers.erase(res);
		}
	}

	void LayerStack::OnUpdate(Timestep ts)
	{
		for (auto it = m_Layers.end(); it != m_Layers.begin(); )
		{
			(*--it)->OnUpdate(ts);
		}
	}
	
	void LayerStack::OnEvent(Event& e)
	{
		for (auto it = m_Layers.end(); it != m_Layers.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
}