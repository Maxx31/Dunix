#pragma once

#include "Core.h"
#include "Dunix/Events/Event.h"
#include "Dunix/Events/WindowEvent.h"
#include "Dunix/Window/Window.h"
#include "Dunix/Editor/ImGuiLayer.h"

#include "LayerStack.h"

namespace Dunix
{
	class DUNIX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }
		static Application& GetApplication() { return *m_Instance; }

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running;

		LayerStack m_LayerStack;
		static Application* m_Instance;

		unsigned int m_VAO, m_VBO;
		class Shader* m_DefaultShader;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
