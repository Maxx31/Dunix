#pragma once

#include "../Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API KeyEvent : public Event
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input)
	};

	class DUNIX_API KeyPressedEvent : public KeyEvent
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input)
	};

	class DUNIX_API KeyReleasedEvent : public KeyEvent
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyEvent)
			EVENT_CLASS_CATEGORY(EventCategory::Input)
	};
}
