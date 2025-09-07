#include "dxpch.h"
#include "Application.h"
#include "WIndow/Window.h"
#include "Log.h"

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
		DX_INFO("Tick");
		Window* mainWindow = Dunix::CreateDunixWindow(props);
		while (true)
		{
			mainWindow->Update();
		}

	}
}