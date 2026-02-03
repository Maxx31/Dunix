#include "dxpch.h"
#include "Application.h"

#include "Dunix/Events/EventDispatcher.h"

#include "Dunix/Renderer/Shader.h"
#include "Dunix/Renderer/Buffer.h"
#include "Dunix/Renderer/Camera.h"
#include "Dunix/Renderer/RenderCommand.h"

#include "Dunix/Core/Input.h"
#include "Dunix/Core/Time.h"
#include "Dunix/Core/Timestep.h"

#include "Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Dunix
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;

		WindowsProps props(1280, 920);

		m_Window = Dunix::CreateDunixWindow(props);
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		RenderCommand::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		m_Instance = nullptr;
	}

	void Application::Run()
	{
		float lastFrameTime = Time::GetTime();

		while (m_Running)
		{
			float time = Time::GetTime();
			Timestep ts = time - lastFrameTime;
			lastFrameTime = time;

			m_LayerStack.OnUpdate(ts);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();
			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_LayerStack.OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
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