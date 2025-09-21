#pragma once
#include "dxpch.h"

#include "../Core/Core.h"
#include <Dunix/Events/Event.h>

namespace Dunix
{

	struct WindowsProps
	{
		WindowsProps(float InWidth, float InHeight)
		{
			Width = InWidth;
			Height = InHeight;
		}
		float Height;
		float Width;
	};

	using EventCallbackFn = std::function<void(Event&)>;

	class DUNIX_API Window
	{
	public:
		virtual ~Window() = 0;
		virtual void Update() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() = 0;
		virtual void SetEventCallback(const EventCallbackFn& cb) = 0;
	};

	std::unique_ptr<Window> CreateDunixWindow(WindowsProps windowProps);
}
