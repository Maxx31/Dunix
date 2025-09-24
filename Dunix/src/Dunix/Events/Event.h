#pragma once
#include "dxpch.h"
#include "../Core/Core.h"

namespace Dunix
{
	//Currently Events are blocking, meaning when event occurs it gets processed immediately
	//In the future we need Event Manager, to process everything during event update

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
	                           virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; } 

	enum class EventType
	{
		None,
		MouseButtonPressedEvent,
		MouseButtonReleasedEvent,
		MouseMovedEvent,
		KeyEvent,
		KeyPressedEvent,
		KeyReleasedEvent,
		WindowResizeEvent,
		WindowCloseEvent
	};

	enum EventCategory
	{
		None = 0,
		App = 1 << 0,
		Input = 1 << 1,
		Keyboard = 1 << 2,
		Mouse = 1 << 3,
	};

	class DUNIX_API Event
	{
	public:
		static EventType GetStaticType() { return EventType::None; }
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }

		bool Handled = false;
	};
	

	inline std::string format_as(const Event& e)
	{
		return e.ToString();
	}
}
