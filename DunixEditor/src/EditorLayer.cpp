#include "dxpch.h"
#include "EditorLayer.h"

#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Core/Input.h"

#include <GLFW/include/GLFW/glfw3.h>
#include <imgui/imgui.h>

namespace Dunix {

    EditorLayer::EditorLayer()
        : Layer()
    {
        //Rendering simple cube 
        float vertices[] =
        {
            // x, y, z
            -0.5f, -0.5f, -0.5f, // 0
             0.5f, -0.5f, -0.5f, // 1
             0.5f,  0.5f, -0.5f, // 2
            -0.5f,  0.5f, -0.5f, // 3
            -0.5f, -0.5f,  0.5f, // 4
             0.5f, -0.5f,  0.5f, // 5
             0.5f,  0.5f,  0.5f, // 6
            -0.5f,  0.5f,  0.5f  // 7
        };

        uint32_t indices[] =
        {
            // back face (-Z)
            0, 1, 2,  2, 3, 0,
            // front face (+Z)
            4, 5, 6,  6, 7, 4,
            // left face (-X)
            4, 7, 3,  3, 0, 4,
            // right face (+X)
            1, 5, 6,  6, 2, 1,
            // bottom face (-Y)
            4, 5, 1,  1, 0, 4,
            // top face (+Y)
            3, 2, 6,  6, 7, 3
        };

        m_Camera = std::make_shared<Camera>(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
        m_Camera->SetRotation(glm::vec3(0.0f, 30.0f, 0.0f)); // looking along -Z

        m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
        m_VBO->SetLayout({
            { ShaderDataType::Float3, "aPos" }   // 3 floats: x, y, z
            });


        m_IBO = IndexBuffer::Create(indices, 36);
        m_VA = VertexArray::Create();

        m_VA->AddVertexBuffer(m_VBO);
        m_VA->SetIndexBuffer(m_IBO);

        m_Shader = Shader::CreateFromFile(
            "assets/shaders/default.vert",
            "assets/shaders/default.frag"
        );

        m_Shader->Bind();
        m_Shader->SetMat4("u_ViewProjection", m_Camera->GetViewProjection());
    }

    EditorLayer::~EditorLayer()
    {
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        // If we have depth testing in RendererAPI, need to clear depth here.
        RenderCommand::SetClearColor({ 0.137f, 0.137f, 0.137f, 1.0f });
        RenderCommand::Clear();

        UpdateCameraPosition(ts);

        glm::vec3 pos(0.0f, 10.0f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos); // Here we can also add scale by multiplying  

        m_Shader->Bind();
        m_Shader->SetMat4("u_ViewProjection", m_Camera->GetViewProjection());
        m_Shader->SetMat4("u_Transform", transform);

        m_VA->Bind();
        RenderCommand::DrawIndexed(m_VA);
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
        }
        return false;
    }

    bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
    {
        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_LEFT)
        {
            Application::Get().GetWindow().SetCursorLocked(true);
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
