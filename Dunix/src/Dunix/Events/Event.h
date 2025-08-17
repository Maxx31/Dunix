#pragma once

#include "../Core.h"

namespace Dunix
{

	//Currently Events are blocking, meaning when event occurs it gets processed immediately
	//In the future we need Event Manager, to process everything during event update

	enum class EventType
	{
		None,
		KeyEvent
	};

	enum EventCategory
	{
		None = 0,
		Input = 1 << 0
	};

	class DUNIX_API Event
	{
	public:
		static EventType GetStaticType() { return EventType::None; }
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		bool Handled = false;
	};
	

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
	                           virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; } 
}
