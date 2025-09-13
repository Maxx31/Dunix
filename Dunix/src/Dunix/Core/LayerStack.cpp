#include "dxpch.h"
#include "LayerStack.h"

namespace Dunix
{
	void LayerStack::PushLayer(Layer* inLayer)
	{
		auto pos = m_Layers.begin() + m_LastLayerIndex;
		m_Layers.insert(pos, inLayer);

		m_LastLayerIndex++;

		inLayer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* inOverLay)
	{
		m_Layers.push_back(inOverLay);

		inOverLay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* inLayer)
	{
		auto endIt = m_Layers.begin() + m_LastLayerIndex;
		auto res = std::find(m_Layers.begin(), endIt, inLayer);

		if (res != endIt)
		{
			inLayer->OnDetach();
			m_Layers.erase(res);
			m_LastLayerIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* inOverlay)
	{
		auto beginIt = m_Layers.begin() + m_LastLayerIndex;
		auto res = std::find(beginIt, m_Layers.end(), inOverlay);

		if (res != m_Layers.end())
		{
			inOverlay->OnDetach();
			m_Layers.erase(res);
		}
	}
	void LayerStack::OnUpdate()
	{
		for (auto it = m_Layers.end(); it != m_Layers.begin(); )
		{
			(*--it)->OnUpdate();
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