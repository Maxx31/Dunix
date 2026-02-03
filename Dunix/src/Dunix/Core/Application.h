#pragma once

#include "Core.h"
#include "Dunix/Events/Event.h"
#include "Dunix/Events/WindowEvent.h"
#include "Dunix/Events/MouseEvent.h"
#include <Dunix/Events/KeyEvent.h>

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

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *m_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		bool m_Running;

		static Application* m_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
