#pragma once

#include "Core.h"
#include "Dunix/Events/Event.h"
#include "Events/WindowEvent.h"
#include "Dunix/Window/Window.h"

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
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
