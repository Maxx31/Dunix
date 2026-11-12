#include "dxpch.h"
#include "WindowGLFW.h"

#include <Dunix/Renderer/OpenGL/OpengGLContext.h>

#include "Dunix/Events/WindowEvent.h"
#include <Dunix/Events/MouseEvent.h>
#include <Dunix/Events/KeyEvent.h>

#include "glad/glad.h"

#include <cmath>

namespace Dunix
{
	namespace
	{
		const char* CursorModeToString(int mode)
		{
			switch (mode)
			{
			case GLFW_CURSOR_NORMAL: return "NORMAL";
			case GLFW_CURSOR_HIDDEN: return "HIDDEN";
			case GLFW_CURSOR_DISABLED: return "DISABLED";
			default: return "UNKNOWN";
			}
		}

		const char* KeyActionToString(int action)
		{
			switch (action)
			{
			case GLFW_PRESS: return "PRESS";
			case GLFW_RELEASE: return "RELEASE";
			case GLFW_REPEAT: return "REPEAT";
			default: return "UNKNOWN";
			}
		}

		bool IsCameraDebugKey(int key)
		{
			return key == GLFW_KEY_W || key == GLFW_KEY_A || key == GLFW_KEY_S ||
				key == GLFW_KEY_D || key == GLFW_KEY_ESCAPE;
		}
	}

	static void GlfwErrorCallback(int code, const char* desc)
	{
		DX_CORE_ERROR("GLFW error {}: {}", code, desc);
	}

	WindowGLFW::WindowGLFW(WindowsProps windowsProps)
	{
		DX_INFO("Window create");
		if (!glfwInit())
		{
			DX_CORE_ERROR("GLFW can't initialize");
		}
		glfwSetErrorCallback(GlfwErrorCallback);

		m_Window = glfwCreateWindow(static_cast<int>(windowsProps.Width), static_cast<int>(windowsProps.Height), "Dunix", nullptr, nullptr);
		m_Data.Width = static_cast<int>(windowsProps.Width);
		m_Data.Height = static_cast<int>(windowsProps.Height);

		if (!m_Window)
		{
			glfwTerminate();
			DX_CORE_ERROR("Can't create GLFW window");
		}

		m_Context = std::make_unique<OpengGLContext>(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSwapInterval(1);

		SetCursorLocked(false);

		//GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& windowData = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				windowData.Width = width;
				windowData.Height = height;

				WindowResizeEvent event(width, height);
				windowData.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				static bool hasLastPos = false;
				static double lastX = 0.0;
				static double lastY = 0.0;
				static int moveEventCount = 0;

				const double dx = hasLastPos ? xpos - lastX : 0.0;
				const double dy = hasLastPos ? ypos - lastY : 0.0;
				++moveEventCount;

				lastX = xpos;
				lastY = ypos;
				hasLastPos = true;

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				if (action == GLFW_PRESS)
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
				}
				else if (action == GLFW_RELEASE)
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& windowData = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				windowData.KeyCode = key;
				windowData.KeyAction = action;

				if (action == GLFW_PRESS)
				{
					KeyPressedEvent event(key);
					windowData.EventCallback(event);
				}
				else if (action == GLFW_RELEASE)
				{
					KeyReleasedEvent event(key);
					windowData.EventCallback(event);
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				WindowCloseEvent event;
				data.EventCallback(event);
			});
	}

	WindowGLFW ::~WindowGLFW()
	{
		if (m_Window) glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowGLFW::Update()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowGLFW::SetCursorLocked(bool locked)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR,
			locked ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);

		glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);

		double xpos = 0.0;
		double ypos = 0.0;
		glfwGetCursorPos(m_Window, &xpos, &ypos);
		
	}

	void* WindowGLFW::GetNativeWindow()
	{
		return m_Window;
	}

	inline void WindowGLFW::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}

	void WindowGLFW::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
	}
}
