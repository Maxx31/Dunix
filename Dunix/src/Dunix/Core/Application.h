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

		template<typename T, typename ...Args>
		T* PushLayer(Args&&...args)
		{
			return m_LayerStack.PushLayer<T>(std::forward<Args>(args)...);
		}
		
		template<typename T, typename ...Args>
		T* PushOverlay(Args&&...args)
		{
			return m_LayerStack.PushOverlay<T>(std::forward<Args>(args)...);
		}
		
		Window& GetWindow()
		{
			return *m_Window;
		}
		
		static Application& Get()
		{
			if (!m_Instance){ DX_CORE_ERROR("Application instance is null!");} 
			return *m_Instance;
		}

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer = nullptr;
		LayerStack m_LayerStack;
		
		bool m_Running = true;

		static Application* m_Instance;
	};

	// To be defined in CPP
std::unique_ptr<Application>  CreateApplication();
}
