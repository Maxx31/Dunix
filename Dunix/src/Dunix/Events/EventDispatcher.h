#pragma once

#include "../Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event){};

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			m_Event.Handled = func(static_cast<T&>(m_Event));
		}

	private:
		Event& m_Event;
	};
}
