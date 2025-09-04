#pragma once

#include "Window.h"
#include <GLFW/glfw3.h>

namespace Dunix
{
	class DUNIX_API WindowGLFW : public Window
	{
	public:

		WindowGLFW(WindowsProps windowsProps);

		virtual ~WindowGLFW() override;
		virtual void Update() override;

		virtual void* GetNativeWindow() override;

	private:
		//GLFWwindow* m_Window;
	};

}
