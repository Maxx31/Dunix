#include "dxpch.h"
#include "WindowGLFW.h"

namespace Dunix
{

	WindowGLFW::WindowGLFW(WindowsProps windowsProps)
	{
		//glfwCreateWindow((int)windowsProps.Height, (int)windowsProps.Width, "Dunix", nullptr, nullptr);
		//m_Window = glfwCreateWindow((int)windowsProps.Height, (int)windowsProps.Width, "Dunix", nullptr, nullptr);
	}

	WindowGLFW ::~WindowGLFW()
	{
	//	glfwDestroyWindow(m_Window);
	}

	void WindowGLFW::Update()
	{

	}

	void* WindowGLFW::GetNativeWindow()
	{
		return this;
	}
}
