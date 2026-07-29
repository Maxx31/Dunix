#include "dxpch.h"
#include "EditorLayer.h"

#include "Dunix/Events/EventDispatcher.h"
#include "Dunix/Renderer/Texture.h"
#include "Dunix/Core/Input.h"
#include "Dunix/Assets/AssetManager.h"
#include "Dunix/Scene/Components.h"
#include "Dunix/Scene/Entity.h"
#include "Dunix/Scene/Scene.h"

#include <GLFW/include/GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <algorithm>

#define DX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Dunix {

    EditorLayer::EditorLayer()
        : Layer()
    {
        m_Camera = std::make_shared<Camera>(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
        m_Camera->SetRotation(glm::vec3(0.0f, 30.0f, 0.0f)); // looking along -Z

        m_ContentBrowserPanel = std::make_shared<ContentBrowserPanel>();
    }

    EditorLayer::~EditorLayer()
    {
    }

    void EditorLayer::OnAttach()
    {
        m_TestTexture = Texture3D::Create("assets/textures/TestTexture.png");
        m_ActiveScene = std::make_shared<Scene>();

        Entity sky = m_ActiveScene->CreateEntity();
        sky.AddComponent<TransformComponent>(
            glm::vec3{ 0.0f, 8.0f, 0.0f },
            glm::vec3{ 0.0f },
            glm::vec3{ 15.0f, 1.0f, 15.0f }
        );
        sky.AddComponent<CubeRendererComponent>(glm::vec4{ 0.4f, 0.7f, 1.0f, 1.0f });

        Entity grass = m_ActiveScene->CreateEntity();
        grass.AddComponent<TransformComponent>(
            glm::vec3{ 0.0f, -8.0f, 0.0f },
            glm::vec3{ 0.0f },
            glm::vec3{ 15.0f, 1.0f, 15.0f }
        );
        grass.AddComponent<CubeRendererComponent>(glm::vec4{ 0.145f, 0.710f, 0.082f, 1.0f });

        SharedPtr<Model> testModel = AssetManager::LoadModel("assets/models/HumanMesh.obj");
        if (testModel)
        {
            Entity importedModel = m_ActiveScene->CreateEntity();
            importedModel.AddComponent<TransformComponent>(
                glm::vec3{ -5.0f, 0.0f, 0.0f },
                glm::vec3{ 0.0f },
                glm::vec3{ 0.2f }
            );
            importedModel.AddComponent<MeshRendererComponent>(testModel, glm::vec4{ 1.0f, 0.85f, 0.25f, 1.0f });
        }
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        m_ActiveScene->OnUpdate(ts);
        
        // If we have depth testing in RendererAPI, need to clear depth here.
        RenderCommand::SetClearColor({ 0.137f, 0.137f, 0.137f, 1.0f });
        RenderCommand::Clear();

        UpdateCameraPosition(ts);

        m_ActiveScene->OnRender(*m_Camera);
    }

    void EditorLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&EditorLayer::OnMouseMoved, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&EditorLayer::OnKeyPressed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&EditorLayer::OnMousePressed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&EditorLayer::OnMouseReleased, this, std::placeholders::_1));
    }

    void EditorLayer::OnImGuiRender(Timestep ts)
    {
        Layer::OnImGuiRender(ts);

        BeginDockspace();

        DrawTopPanel();
        DrawSceneViewport();
        DrawSettingsPanel();
        m_ContentBrowserPanel->OnImGuiRender();

        EndDockspace();
    }

    bool EditorLayer::OnMouseMoved(MouseMovedEvent& e)
    {
        if (!m_ViewportCameraActive)
            return false;

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

        rot.x = std::clamp(rot.x, -89.0f, 89.0f);
        if (rot.y > 180.0f)
            rot.y -= 360.0f;
        else if (rot.y < -180.0f)
            rot.y += 360.0f;

        m_Camera->SetRotation(rot);
        return false;
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
        {
            Application::Get().GetWindow().SetCursorLocked(false);
            m_FirstMouse = true;
            m_ViewportCameraActive = false;
            return true;
        }
        return false;
    }

    bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
    {
        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_RIGHT && m_ViewportHovered)
        {
            Application::Get().GetWindow().SetCursorLocked(true);
            m_FirstMouse = true;
            m_ViewportCameraActive = true;
            return true;
        }

        return false;
    }

    bool EditorLayer::OnMouseReleased(MouseButtonReleasedEvent& e)
    {
        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_RIGHT)
        {
            Application::Get().GetWindow().SetCursorLocked(false);
            m_FirstMouse = true;
            m_ViewportCameraActive = false;
            return true;
        }
        return false;
    }

    void EditorLayer::UpdateCameraPosition(float dt)
    {
        if (!m_ViewportCameraActive)
            return;

        float speed = 5.0f * dt;
        glm::vec3 pos = m_Camera->GetPosition();
        bool moved = false;

        if (Input::IsKeyPressed(GLFW_KEY_W)) { pos += m_Camera->GetForward() * speed; moved = true; }
        if (Input::IsKeyPressed(GLFW_KEY_S)) { pos -= m_Camera->GetForward() * speed; moved = true; }
        if (Input::IsKeyPressed(GLFW_KEY_A)) { pos -= m_Camera->GetRight() * speed; moved = true; }
        if (Input::IsKeyPressed(GLFW_KEY_D)) { pos += m_Camera->GetRight() * speed; moved = true; }

        if (moved)
            m_Camera->SetPosition(pos);
    }

    void EditorLayer::BeginDockspace()
    {
        static bool dockspaceOpen = true;
        static bool firstTime = true;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Editor Dockspace", &dockspaceOpen, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspaceID = ImGui::GetID("EditorDockspace");
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

        bool buildDefaultLayout = firstTime && ImGui::DockBuilderGetNode(dockspaceID) == nullptr;
        firstTime = false;

        if (buildDefaultLayout)
        {
            ImGui::DockBuilderRemoveNode(dockspaceID);
            ImGui::DockBuilderAddNode(dockspaceID, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);

            ImGuiID dockMainID = dockspaceID;
            ImGuiID dockTopID = 0;
            ImGuiID dockBottomID = 0;
            ImGuiID dockRightID = 0;

            ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Up, 0.08f, &dockTopID, &dockMainID);
            ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Down, 0.25f, &dockBottomID, &dockMainID);
            ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Right, 0.25f, &dockRightID, &dockMainID);

            ImGui::DockBuilderDockWindow("Top Panel", dockTopID);
            ImGui::DockBuilderDockWindow("Viewport", dockMainID);
            ImGui::DockBuilderDockWindow("Settings", dockRightID);
            ImGui::DockBuilderDockWindow("Content Browser", dockBottomID);
            ImGui::DockBuilderFinish(dockspaceID);
        }

        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), dockspaceFlags);
    }

    void EditorLayer::DrawSceneViewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
        auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();

        auto viewportOffset = ImGui::GetWindowPos();
        m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
        m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        Application::Get().GetImGuiLayer()->BlockEvents(!(m_ViewportHovered || m_ViewportCameraActive));

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::DrawTopPanel()
    {
        ImGui::Begin("Top Panel", nullptr, ImGuiWindowFlags_MenuBar);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("New Scene"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    void EditorLayer::DrawSettingsPanel()
    {
        ImGui::Begin("Settings");

        ImGui::Text("Transform");
        ImGui::Separator();
        ImGui::TextDisabled("Select an entity to edit its transform.");

        ImGui::End();
    }

    void EditorLayer::EndDockspace()
    {
        ImGui::End();
    }
}
