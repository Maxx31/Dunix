#include "dxpch.h"
#include "WindowGLFW.h"

namespace Dunix
{

	static void GlfwErrorCallback(int code, const char* desc)
	{
		DX_CORE_ERROR("GLFW error {}: {}", code, desc);
	}

	WindowGLFW::WindowGLFW(WindowsProps windowsProps)
	{
		DX_INFO("Window create");
		if (!glfwInit())
		{
			DX_ERROR("GLFW can't initialize");
		}

		glfwSetErrorCallback(GlfwErrorCallback);
		m_Window = glfwCreateWindow((int)windowsProps.Width, (int)windowsProps.Height, "Dunix", nullptr, nullptr);

		if (!m_Window)
		{
			glfwTerminate();
			DX_ERROR("Can't create GLFW window");
		}

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);
	}

	WindowGLFW ::~WindowGLFW()
	{
		if (m_Window) glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowGLFW::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_Window);
		glfwPollEvents();   
	}

	void* WindowGLFW::GetNativeWindow()
	{
		return this;
	}
}
