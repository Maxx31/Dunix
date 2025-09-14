#pragma once

#include "Window.h"
#include <glad/glad.h>
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
		inline void SetEventCallback(const EventCallbackFn& callback) override;

	private:
		//Event callbacks
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			int KeyCode, KeyAction;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
