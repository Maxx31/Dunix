#include "dxpch.h"
#include "Application.h"
#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Events/WindowEvent.h"
#include "Log.h"

namespace Dunix
{
	Application::Application()
	{
		WindowsProps props(1280, 920);
		m_Window = Dunix::CreateDunixWindow(props);

		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		m_Running = true;
		while (m_Running)
		{
			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		DX_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		DX_CORE_INFO("Close application");
		return true;
	}
}