#pragma once

#include <Dunix.h>

#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#include "Dunix/Core/Timestep.h"
#include "Dunix/Core/Layer.h"

#include "Dunix/Events/KeyEvent.h"
#include "Dunix/Events/MouseEvent.h"

#include "Dunix/Renderer/Shader.h"
#include "Dunix/Renderer/Buffer.h"
#include "Dunix/Renderer/Camera.h"
#include "Dunix/Renderer/RenderCommand.h"

namespace Dunix
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer() override;

		void OnAttach() override;
		void OnUpdate(Timestep ts) override;
		void OnEvent(Event& e) override;
		void OnImGuiRender(Timestep ts) override;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);
		bool OnMouseReleased(MouseButtonReleasedEvent& e);

		void NewScene();
		void CreateDefaultScene();
		void UpdateCameraPosition(float dt);

		//ImGui UI related funcs
		void BeginDockspace();

		void DrawSceneViewport();
		void DrawTopPanel();
		void EndDockspace();

	private:
		std::shared_ptr<class Camera> m_Camera;
		class VertexArray* m_VA;
		class VertexBuffer* m_VBO;
		class IndexBuffer* m_IBO;

		class Shader* m_Shader;

		SharedPtr<class Texture3D> m_TestTexture;
		SharedPtr<class Scene> m_ActiveScene;

		bool  m_FirstMouse = true;
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
		bool  m_ViewportFocused = false;
		bool  m_ViewportHovered = false;
		bool  m_ViewportCameraActive = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2] = {};

		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
		SharedPtr<ContentBrowserPanel> m_ContentBrowserPanel;
	};
}

