#include "dxpch.h"
#include "EditorLayer.h"

#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Renderer/Texture.h"
#include "Dunix/Core/Input.h"

#include <GLFW/include/GLFW/glfw3.h>
#include <imgui/imgui.h>

namespace Dunix {

    EditorLayer::EditorLayer()
        : Layer()
    {
        m_Camera = std::make_shared<Camera>(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
        m_Camera->SetRotation(glm::vec3(0.0f, 30.0f, 0.0f)); // looking along -Z
    }

    EditorLayer::~EditorLayer()
    {
    }

    void EditorLayer::OnAttach()
    {
        m_TestTexture = Texture3D::Create("assets/textures/Checkerboard.png");
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        // If we have depth testing in RendererAPI, need to clear depth here.
        RenderCommand::SetClearColor({ 0.137f, 0.137f, 0.137f, 1.0f });
        RenderCommand::Clear();

        UpdateCameraPosition(ts);

        Renderer3D::BeginScene(*m_Camera);
        Renderer3D::DrawCube({ 0.0f, 0.0f, 0.0f }, { 2.0f, 2.0f, 2.0f }, { 0.0f, 0.0f, 1.0f, 1.0f });
        Renderer3D::DrawCube({ 5.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 3.0f }, m_TestTexture);
        Renderer3D::EndScene();
    }

    void EditorLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&EditorLayer::OnMouseMoved, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&EditorLayer::OnKeyPressed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&EditorLayer::OnMousePressed, this, std::placeholders::_1));
    }

    bool EditorLayer::OnMouseMoved(MouseMovedEvent& e)
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
        float yoffset = m_LastMouseY - ypos;

        m_LastMouseX = xpos;
        m_LastMouseY = ypos;

        const float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        glm::vec3 rot = m_Camera->GetRotation();
        rot.x += yoffset;
        rot.y -= xoffset;

        if (rot.x > 89.0f)  rot.x = 89.0f;
        if (rot.x < -89.0f) rot.x = -89.0f;

        m_Camera->SetRotation(rot);
        return false;
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
        {
            Application::Get().GetWindow().SetCursorLocked(false);
            m_FirstMouse = true;
        }
        return false;
    }

    bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
    {
        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_LEFT)
        {
            Application::Get().GetWindow().SetCursorLocked(true);
            m_FirstMouse = true;
        }
        return false;
    }

    void EditorLayer::UpdateCameraPosition(float dt)
    {
        float speed = 5.0f * dt;
        glm::vec3 pos = m_Camera->GetPosition();

        if (Input::IsKeyPressed(GLFW_KEY_W)) pos += m_Camera->GetForward() * speed;
        if (Input::IsKeyPressed(GLFW_KEY_S)) pos -= m_Camera->GetForward() * speed;
        if (Input::IsKeyPressed(GLFW_KEY_A)) pos -= m_Camera->GetRight() * speed;
        if (Input::IsKeyPressed(GLFW_KEY_D)) pos += m_Camera->GetRight() * speed;

        m_Camera->SetPosition(pos);
    }

    void EditorLayer::OnImGuiRender()
    {
        ImGui::Begin("Editor");
        ImGui::Text("Viewport running");
        ImGui::End();
    }
}
