#include "dxpch.h"
#include "WindowGLFW.h"
#include "Window.h"

namespace Dunix
{

	Window::~Window()
	{
	}

	Window* CreateDunixWindow(WindowsProps props)
	{
		return new WindowGLFW(props);
	}
}
