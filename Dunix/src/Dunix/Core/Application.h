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

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);

		void UpdateCameraPosition(float deltaTime);

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

		unsigned int m_VAO; //Vertex Array Object

		std::shared_ptr<class Camera> m_Camera;
		class VertexArray* m_VA;
		class VertexBuffer* m_VBO; //Vertex Buffer Object
		class IndexBuffer* m_IBO; //Index Buffer Object
		class Shader* m_Shader;

		bool  m_FirstMouse = true;
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
