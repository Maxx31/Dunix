#include "dxpch.h"
#include "Application.h"
#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Events/WindowEvent.h"
#include "Log.h"

namespace Dunix
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		WindowsProps props(1280, 920);
		m_Window = Dunix::CreateDunixWindow(props);

		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		m_Instance = this;
	}

	Application::~Application()
	{
		m_Instance = nullptr;
	}

	void Application::Run()
	{
		m_Running = true;
		while (m_Running)
		{
			m_Window->Update();
			m_LayerStack.OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_LayerStack.OnEvent(e);
		DX_CORE_INFO("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		DX_CORE_INFO("Close application");
		return true;
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
}