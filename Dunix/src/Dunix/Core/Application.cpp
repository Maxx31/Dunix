#include "dxpch.h"
#include "Application.h"
#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Events/WindowEvent.h"
#include "Dunix/Renderer/Shader.h"
#include "Log.h"

#include <glad/glad.h>

namespace Dunix
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;
		WindowsProps props(1280, 920);
		m_Window = Dunix::CreateDunixWindow(props);

		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//Rendering simple triangle 
		float vertices[] = {
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.0f,  0.5f
		};

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glBindVertexArray(0);

		//Shader

		m_DefaultShader = Shader::CreateFromFile(
			"assets/shaders/default.vert",
			"assets/shaders/default.frag"
		);
	}

	Application::~Application()
	{
		m_Instance = nullptr;
	}

	void Application::Run()
	{
		m_DefaultShader->Bind();
		while (m_Running)
		{
			glClearColor(0.137, 0.137, 0.137, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);

			m_LayerStack.OnUpdate();

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