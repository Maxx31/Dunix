#pragma once

#include "../Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API KeyEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(KeyEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input)
	};
}
