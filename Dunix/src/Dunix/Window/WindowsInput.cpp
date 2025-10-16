#include "dxpch.h"
#include "WindowsInput.h"

#include "../Core/Application.h"
#include <GLFW/glfw3.h>

namespace Dunix
{
	Input* Input::m_instance = new WindowsInput();

	bool Dunix::WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* WindowsWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

		if (WindowsWindow)
		{
			auto state = glfwGetKey(WindowsWindow, button);
			return state == GLFW_PRESS;
		}
		
		return false;
	}

	bool Dunix::WindowsInput::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* WindowsWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

		if (WindowsWindow)
		{
			auto state = glfwGetMouseButton(WindowsWindow, keycode);
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}

		return false;
	}

	std::pair<float, float> Dunix::WindowsInput::GetMousePositionImpl()
	{
		GLFWwindow* WindowsWindow = static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());

		if (WindowsWindow)
		{
			double xPos, yPos;
			glfwGetCursorPos(WindowsWindow, &xPos, &yPos);
			return { (float)xPos, (float)yPos };
		}
		return { 0.0f, 0.0f };
	}

	float Dunix::WindowsInput::GetMousePosXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float Dunix::WindowsInput::GetMousePosYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
