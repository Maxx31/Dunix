#pragma once

#include "../Core/Core.h"
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
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)
	};

	class DUNIX_API KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(unsigned int keyCode)
			: m_KeyCode(keyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent";
			return ss.str();
		}
		inline unsigned int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_TYPE(KeyEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

	private:
		unsigned int m_KeyCode;
	};

	class DUNIX_API KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(unsigned int keyCode)
			: m_KeyCode(keyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent";
			return ss.str();
		}

		inline unsigned int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_TYPE(KeyEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

	private:
		unsigned int m_KeyCode;
	};

	class DUNIX_API KeyTypedEvent : public KeyEvent
	{
	public:

		KeyTypedEvent(unsigned int keyCode)
			: m_KeyCode(keyCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent";
			return ss.str();
		}

		inline unsigned int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_TYPE(KeyTypedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::Input | EventCategory::Keyboard)

	private:
		unsigned int m_KeyCode;
	};
}
