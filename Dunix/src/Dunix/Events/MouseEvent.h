#pragma once

#include "../Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API MouseButtonPressed : public Event
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

	class DUNIX_API MouseButtonReleased : public KeyEvent
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

	class DUNIX_API MouseMovedEvent : public KeyEvent
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
}
