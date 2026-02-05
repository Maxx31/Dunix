#pragma once

#include "Dunix/Events/Event.h"
#include "Dunix/Core/Timestep.h"

namespace Dunix
{
	class DUNIX_API Layer
	{
	public:
		explicit Layer(std::string name = "Layer") : m_DebugName(std::move(name)){}
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}
	private:
		std::string m_DebugName;
	};
}

