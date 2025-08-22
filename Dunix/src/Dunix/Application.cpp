#include "dxpch.h"
#include "Application.h"
#include "WIndow/Window.h"

namespace Dunix
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowsProps props(1280, 920);
		Dunix::CreateDunixWindow(props);

		while (true);
	}
}