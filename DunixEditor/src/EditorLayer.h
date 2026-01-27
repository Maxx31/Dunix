#pragma once

#include <Dunix.h>
#include "Dunix/Renderer/Shader.h"
#include "Dunix/Renderer/Buffer.h"
#include "Dunix/Renderer/Camera.h"
#include "Dunix/Core/Timestep.h"
#include "Dunix/Renderer/RenderCommand.h"

#include <imgui/imgui.h>

using namespace Dunix;

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
	std::shared_ptr<Camera> m_Camera;

	std::shared_ptr<VertexArray>  m_VA;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<IndexBuffer>  m_IBO;
	std::shared_ptr<Shader>       m_Shader;

	bool  m_FirstMouse = true;
	float m_LastMouseX = 0.0f;
	float m_LastMouseY = 0.0f;

};

