#pragma once

#include "Core.h"
#include "Dunix/Events/Event.h"
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
	private:
		std::unique_ptr<Window> m_Window;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
