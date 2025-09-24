#pragma once

#include "../Core/Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API WindowResizeEvent : public Event
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent";
			return ss.str();
		}
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height)
		{
		}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResizeEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input)

	private:
		unsigned int m_Width, m_Height;
	};

	class DUNIX_API WindowCloseEvent : public Event
	{
	public:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowCloseEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input)
	};
}
