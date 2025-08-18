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
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}
