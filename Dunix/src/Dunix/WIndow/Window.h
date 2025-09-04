#pragma once

#include "../Core.h"

namespace Dunix
{
	struct WindowsProps
	{
		WindowsProps(float InHeight, float InWidth)
		{
			Height = InHeight;
			Width = InWidth;
		}
		float Height;
		float Width;
	};


	class DUNIX_API Window
	{
	public:
		virtual ~Window() = 0;
		virtual void Update() = 0;

		virtual void* GetNativeWindow() = 0;
	};

	Window* CreateDunixWindow(WindowsProps windowProps);
}
