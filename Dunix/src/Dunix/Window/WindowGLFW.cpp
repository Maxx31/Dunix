#include "dxpch.h"
#include "WindowGLFW.h"
#include "Dunix/Events/WindowEvent.h"

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
		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSwapInterval(1);

		//GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& windowData = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			windowData.Width = width;
			windowData.Height = height;

			WindowResizeEvent event(width, height);
			windowData.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& windowData = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{

				}
				else if (action == GLFW_RELEASE)
				{

				}
			});
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

	inline void WindowGLFW::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}

	void WindowGLFW::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	}
}
