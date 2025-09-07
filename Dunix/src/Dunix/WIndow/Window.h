#pragma once

#include "../Core.h"

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


	class DUNIX_API Window
	{
	public:
		virtual ~Window() = 0;
		virtual void Update() = 0;

		virtual void* GetNativeWindow() = 0;
	};

	Window* CreateDunixWindow(WindowsProps windowProps);
}
