#pragma once

#include <Dunix.h>

#include "Dunix/Core/Timestep.h"
#include "Dunix/Core/Layer.h"

#include "Dunix/Renderer/Shader.h"
#include "Dunix/Renderer/Buffer.h"
#include "Dunix/Renderer/Camera.h"
#include "Dunix/Renderer/RenderCommand.h"

#include <imgui/imgui.h>


namespace Dunix
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnUpdate(Timestep ts) override;
		void OnEvent(Event& e) override;
		void OnImGuiRender() override;


	private:
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);

		void UpdateCameraPosition(float dt);


	private:
		std::shared_ptr<class Camera> m_Camera;
		class VertexArray* m_VA;
		class VertexBuffer* m_VBO;
		class IndexBuffer* m_IBO;

		class Shader* m_Shader;

		bool  m_FirstMouse = true;
		float m_LastMouseX = 0.0f;
		float m_LastMouseY = 0.0f;
	};
}

