#include "dxpch.h"
#include "Application.h"

#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Events/WindowEvent.h"
#include "Dunix/Renderer/Shader.h"
#include "Dunix/Renderer/Buffer.h"

#include "Dunix/Renderer/Camera.h"

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
		-0.5f, -0.5f, 0.0f,   // vertex 0
		0.5f, -0.5f, 0.0f,   // vertex 1
		0.0f,  0.5f, 0.0f    // vertex 2
		};

		uint32_t indices[] = { 0, 1, 2 };

		m_Camera = std::make_shared<Camera>(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

		m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
		m_Camera->SetRotation(glm::vec3(0.0f, 30.0f, 0.0f)); // looking along -Z

		m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
		m_VBO->SetLayout({
			{ ShaderDataType::Float3, "aPos" }   // 3 floats: x, y, z
		});

		m_IBO = IndexBuffer::Create(indices, 3);
		m_VA = VertexArray::Create();

		m_VA->AddVertexBuffer(m_VBO);
		m_VA->SetIndexBuffer(m_IBO);

		m_Shader = Shader::CreateFromFile(
			"assets/shaders/default.vert",
			"assets/shaders/default.frag"
		);

		glm::mat4 viewProj = m_Camera->GetViewProjection();  // put a breakpoint here
		m_Shader->Bind();

		m_Shader->SetMat4("u_ViewProjection", viewProj);
		m_Shader->SetMat4("u_ViewProjection", m_Camera->GetViewProjection());
	}

	Application::~Application()
	{
		m_Instance = nullptr;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.137, 0.137, 0.137, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//m_Shader->Bind();
			m_VA->Bind();

			glDrawElements(GL_TRIANGLES, m_IBO->GetCount(), GL_UNSIGNED_INT, nullptr);

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