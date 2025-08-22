#pragma once

#include "Window.h"

namespace Dunix
{
	class DUNIX_API GLFWWindow : public Window
	{
	public:

		GLFWWindow(WindowsProps windowsProps);

	//	virtual ~GLFWWindow() override;
		virtual void Update() override;

		virtual void* GetNativeWindow() override;
	};

}
