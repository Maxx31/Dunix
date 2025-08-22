#include "dxpch.h"
#include "GLFWWindow.h"
#include "Window.h"

namespace Dunix
{
	Window* CreateDunixWindow(WindowsProps props)
	{
		return new GLFWWindow(props);
	}
}
