#include "dxpch.h"
#include "WindowGLFW.h"
#include "Window.h"

namespace Dunix
{
	Window::~Window() = default;

	std::unique_ptr<Window> CreateDunixWindow(WindowsProps props)
	{
		return std::make_unique<WindowGLFW>(props);
	}
}
