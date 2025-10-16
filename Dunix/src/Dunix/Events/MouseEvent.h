#pragma once

#include "../Core/Core.h"
#include "Event.h"

namespace Dunix
{
	class DUNIX_API MouseMovedEvent : public Event
	{
	public:

		MouseMovedEvent(float inPosX, float inPosY)
			: m_PosX(inPosX), m_PosY(inPosY) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent";
			return ss.str();
		}

		inline float GetPosX() const { return m_PosX; }
		inline float GetPosY() const { return m_PosY; }

		EVENT_CLASS_TYPE(MouseMovedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)

	private:
		float m_PosX, m_PosY;
	};

	class DUNIX_API MouseButtonEvent : public Event
	{
	public:

		MouseButtonEvent(int inButtonCode)
			:m_ButtonCode(inButtonCode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonEvent";
			return ss.str();
		}

		inline unsigned int GetButtonCode() const { return m_ButtonCode; }

		EVENT_CLASS_TYPE(MouseButtonEvent)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)

	private:
		unsigned int m_ButtonCode;
	};

	class DUNIX_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int inButtonCode) : MouseButtonEvent(inButtonCode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)
	};

	class DUNIX_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int inButtonCode) : MouseButtonEvent(inButtonCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased";
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleasedEvent)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)
	};

	class DUNIX_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolledEvent)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryInput | EventCategory::CategoryMouse)
	private:
		float m_XOffset, m_YOffset;
	};
}
