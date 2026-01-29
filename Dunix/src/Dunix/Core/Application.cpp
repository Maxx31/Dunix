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
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&Application::OnMouseMoved, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&Application::OnKeyPressed, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&Application::OnMousePressed, this, std::placeholders::_1));

		m_LayerStack.OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{
		float xpos = e.GetPosX();
		float ypos = e.GetPosY();

		if (m_FirstMouse)
		{
			m_LastMouseX = xpos;
			m_LastMouseY = ypos;
			m_FirstMouse = false;
			return false;
		}

		float xoffset = xpos - m_LastMouseX;
		float yoffset = m_LastMouseY - ypos; // inverted Y (screen vs world)

		m_LastMouseX = xpos;
		m_LastMouseY = ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		glm::vec3 rot = m_Camera->GetRotation();
		rot.x += yoffset; // pitch
		rot.y -= xoffset; // yaw

		// clamp pitch
		if (rot.x > 89.0f)  rot.x = 89.0f;
		if (rot.x < -89.0f) rot.x = -89.0f;

		m_Camera->SetRotation(rot);
		return false;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
		{
			m_Window->SetCursorLocked(false);
		}
		return true;
	}

	bool Application::OnMousePressed(MouseButtonPressedEvent& e)
	{
		if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_LEFT)
		{
			m_Window->SetCursorLocked(true);
		}
		return true;
	}

	void Application::UpdateCameraPosition(float deltaTime)
	{
		float speed = 5.0f * deltaTime;
		glm::vec3 pos = m_Camera->GetPosition();

		if (Input::IsKeyPressed(GLFW_KEY_W))
			pos += m_Camera->GetForward() * speed;
		if (Input::IsKeyPressed(GLFW_KEY_S))
			pos -= m_Camera->GetForward() * speed;
		if (Input::IsKeyPressed(GLFW_KEY_A))
			pos -= m_Camera->GetRight() * speed;
		if (Input::IsKeyPressed(GLFW_KEY_D))
			pos += m_Camera->GetRight() * speed;

		m_Camera->SetPosition(pos);
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