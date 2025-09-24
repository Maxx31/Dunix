#pragma once

#include "../Core/Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API MouseButtonPressedEvent : public Event
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
	};

	class DUNIX_API MouseButtonReleasedEvent : public Event
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleasedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
	};

	class DUNIX_API MouseMovedEvent : public Event
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMovedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Mouse)
	};
}
