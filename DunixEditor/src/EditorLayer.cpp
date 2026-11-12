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
#include <cmath>

#define DX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Dunix {
    namespace
    {
        bool ShouldLogMouseDelta(int count, float xoffset, float yoffset)
        {
            return count <= 20 || count % 30 == 0 ||
                std::abs(xoffset) > 50.0f || std::abs(yoffset) > 50.0f;
        }
    }

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
       
        //Test values for now, in the future need to get vieport size 
        FramebufferSpecification fbSpec;
        fbSpec.Width = 1280;
        fbSpec.Height = 720;
        fbSpec.Attachments = {
            FramebufferTextureFormat::RGBA8,
            FramebufferTextureFormat::RED_INTEGER,
            FramebufferTextureFormat::Depth
        };
        
        m_Framebuffer = Framebuffer::Create(fbSpec);
        
        NewScene();
    }

    void EditorLayer::NewScene()
    {
        m_ActiveScene = std::make_shared<Scene>();
        m_SceneHierarchyPanel.SetNewContext(m_ActiveScene);

        CreateDefaultScene();
    }

    void EditorLayer::CreateDefaultScene()
    {
        Entity sky = m_ActiveScene->CreateEntity("Sky");
        auto& skyTransform = sky.GetComponent<TransformComponent>();
        skyTransform.Position = glm::vec3(0.0f, 8.0f, 0.0f);
        skyTransform.Scale = glm::vec3(15.0f, 1.0f, 15.0f);
        sky.AddComponent<CubeRendererComponent>(glm::vec4{ 0.4f, 0.7f, 1.0f, 1.0f });

        Entity grass = m_ActiveScene->CreateEntity("Grass");
        auto& grassTransform = grass.GetComponent<TransformComponent>();
        grassTransform.Position = glm::vec3(0.0f, -8.0f, 0.0f);
        grassTransform.Rotation = glm::vec3(0.0f);
        grassTransform.Scale = glm::vec3(15.0f, 1.0f, 15.0f);
        grass.AddComponent<CubeRendererComponent>(glm::vec4{ 0.145f, 0.710f, 0.082f, 1.0f });

        SharedPtr<Model> testModel = AssetManager::LoadModel("assets/models/HumanMesh.obj");
        if (testModel)
        {
            Entity importedModel = m_ActiveScene->CreateEntity("HumanMesh");
            auto& modelTransform = importedModel.GetComponent<TransformComponent>();
            modelTransform.Position = glm::vec3(-5.0f, 0.0f, 0.0f);
            modelTransform.Rotation = glm::vec3(0.0f);
            modelTransform.Scale = glm::vec3(0.2f);
            importedModel.AddComponent<MeshRendererComponent>(testModel, glm::vec4{ 1.0f, 0.85f, 0.25f, 1.0f });
        }
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        m_ActiveScene->OnUpdate(ts);

        FramebufferSpecification spec = m_Framebuffer->GetSpecification();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f &&
            (spec.Width != static_cast<uint32_t>(m_ViewportSize.x) || spec.Height != static_cast<uint32_t>(m_ViewportSize.y)))
        {
            m_Framebuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
        }
        
        // If we have depth testing in RendererAPI, need to clear depth here.
        m_Framebuffer->Bind();
        
        RenderCommand::SetClearColor({ 0.137f, 0.137f, 0.137f, 1.0f });
        RenderCommand::Clear();
        m_Framebuffer->ClearAttachment(1, -1);

        UpdateCameraPosition(ts);

        m_ActiveScene->OnRender(*m_Camera);
        CheckForHoveredEntity();
        
        m_Framebuffer->Unbind();
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
        m_SceneHierarchyPanel.OnImGuiRender();
        m_ContentBrowserPanel->OnImGuiRender();

        EndDockspace();
    }

    bool EditorLayer::OnWindowClose(WindowCloseEvent& e)
    {
        return true;
    }

    bool EditorLayer::OnMouseMoved(MouseMovedEvent& e)
    {
        if (!m_ViewportCameraActive)
            return false;

        static int activeMouseMoveCount = 0;
        ++activeMouseMoveCount;

        float xpos = e.GetPosX();
        float ypos = e.GetPosY();
        const glm::vec2 viewportCenter = {
            (m_ViewportBounds[0].x + m_ViewportBounds[1].x) * 0.5f,
            (m_ViewportBounds[0].y + m_ViewportBounds[1].y) * 0.5f
        };

        if (m_FirstMouse)
        {
            m_FirstMouse = false;

            std::cout << "[InputDebug][Editor] Mouse baseline"
                << " count=" << activeMouseMoveCount
                << " pos=(" << xpos << ", " << ypos << ")"
                << " center=(" << viewportCenter.x << ", " << viewportCenter.y << ")"
                << " viewportHovered=" << m_ViewportHovered
                << " viewportFocused=" << m_ViewportFocused
                << " viewportBoundsMin=(" << m_ViewportBounds[0].x << ", " << m_ViewportBounds[0].y << ")"
                << " viewportBoundsMax=(" << m_ViewportBounds[1].x << ", " << m_ViewportBounds[1].y << ")"
                << std::endl;
            return false;
        }

        float xoffset = xpos - viewportCenter.x;
        float yoffset = viewportCenter.y - ypos;
        const float rawXOffset = xoffset;
        const float rawYOffset = yoffset;

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

        if (ShouldLogMouseDelta(activeMouseMoveCount, rawXOffset, rawYOffset))
        {
            const glm::vec3 currentRot = m_Camera->GetRotation();
            std::cout << "[InputDebug][Editor] Mouse camera delta"
                << " count=" << activeMouseMoveCount
                << " pos=(" << xpos << ", " << ypos << ")"
                << " center=(" << viewportCenter.x << ", " << viewportCenter.y << ")"
                << " rawDelta=(" << rawXOffset << ", " << rawYOffset << ")"
                << " scaledDelta=(" << xoffset << ", " << yoffset << ")"
                << " rotBefore=(" << currentRot.x << ", " << currentRot.y << ", " << currentRot.z << ")"
                << " rotAfter=(" << rot.x << ", " << rot.y << ", " << rot.z << ")"
                << " viewportHovered=" << m_ViewportHovered
                << " viewportFocused=" << m_ViewportFocused
                << std::endl;
        }

        m_Camera->SetRotation(rot);

        if (std::abs(rawXOffset) > 0.0f || std::abs(rawYOffset) > 0.0f)
            CenterMouseInViewport();

        return false;
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        if (e.GetKeyCode() == GLFW_KEY_W || e.GetKeyCode() == GLFW_KEY_A ||
            e.GetKeyCode() == GLFW_KEY_S || e.GetKeyCode() == GLFW_KEY_D ||
            e.GetKeyCode() == GLFW_KEY_ESCAPE)
        {
            std::cout << "[InputDebug][Editor] KeyPressed"
                << " key=" << e.GetKeyCode()
                << " cameraActive=" << m_ViewportCameraActive
                << " viewportHovered=" << m_ViewportHovered
                << " viewportFocused=" << m_ViewportFocused
                << std::endl;
        }

        if (e.GetKeyCode() == GLFW_KEY_ESCAPE)
        {
            DeactivateViewportCamera();
            return true;
        }
        return false;
    }

    bool EditorLayer::OnMousePressed(MouseButtonPressedEvent& e)
    {
        std::cout << "[InputDebug][Editor] MousePressed"
            << " button=" << e.GetButtonCode()
            << " viewportHovered=" << m_ViewportHovered
            << " viewportFocused=" << m_ViewportFocused
            << " cameraActive=" << m_ViewportCameraActive
            << std::endl;

        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_RIGHT && (m_ViewportHovered || m_ViewportCameraActive))
        {
            if (m_ViewportCameraActive)
                DeactivateViewportCamera();
            else
                ActivateViewportCamera();

            return true;
        }

        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_LEFT && m_ViewportHovered)
        {
            m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
        }
        return false;
    }

    bool EditorLayer::OnMouseReleased(MouseButtonReleasedEvent& e)
    {
        std::cout << "[InputDebug][Editor] MouseReleased"
            << " button=" << e.GetButtonCode()
            << " viewportHovered=" << m_ViewportHovered
            << " viewportFocused=" << m_ViewportFocused
            << " cameraActive=" << m_ViewportCameraActive
            << std::endl;

        if (e.GetButtonCode() == GLFW_MOUSE_BUTTON_RIGHT)
        {
            std::cout << "[InputDebug][Editor] RMB release ignored; camera toggles on press" << std::endl;
            return true;
        }
        return false;
    }

    void EditorLayer::ActivateViewportCamera()
    {
        Application::Get().GetWindow().SetCursorLocked(true);
        m_ViewportCameraActive = true;
        m_FirstMouse = false;
        CenterMouseInViewport();

        std::cout << "[InputDebug][Editor] Camera activated by right mouse"
            << " viewportBoundsMin=(" << m_ViewportBounds[0].x << ", " << m_ViewportBounds[0].y << ")"
            << " viewportBoundsMax=(" << m_ViewportBounds[1].x << ", " << m_ViewportBounds[1].y << ")"
            << " viewportSize=(" << m_ViewportSize.x << ", " << m_ViewportSize.y << ")"
            << std::endl;
    }

    void EditorLayer::DeactivateViewportCamera()
    {
        if (!m_ViewportCameraActive)
            return;

        Application::Get().GetWindow().SetCursorLocked(false);
        m_FirstMouse = true;
        m_ViewportCameraActive = false;
        std::cout << "[InputDebug][Editor] Camera deactivated" << std::endl;
    }

    void EditorLayer::CenterMouseInViewport()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        if (!window)
            return;

        const double centerX = (m_ViewportBounds[0].x + m_ViewportBounds[1].x) * 0.5;
        const double centerY = (m_ViewportBounds[0].y + m_ViewportBounds[1].y) * 0.5;
        glfwSetCursorPos(window, centerX, centerY);
    }

    void EditorLayer::UpdateCameraPosition(float dt)
    {
        if (!m_ViewportCameraActive)
            return;

        float speed = 5.0f * dt;
        glm::vec3 pos = m_Camera->GetPosition();
        bool moved = false;

        const bool wPressed = Input::IsKeyPressed(GLFW_KEY_W);
        const bool sPressed = Input::IsKeyPressed(GLFW_KEY_S);
        const bool aPressed = Input::IsKeyPressed(GLFW_KEY_A);
        const bool dPressed = Input::IsKeyPressed(GLFW_KEY_D);

        static int activeCameraFrameCount = 0;
        static bool lastWPressed = false;
        static bool lastSPressed = false;
        static bool lastAPressed = false;
        static bool lastDPressed = false;
        ++activeCameraFrameCount;

        const bool keyStateChanged = wPressed != lastWPressed || sPressed != lastSPressed ||
            aPressed != lastAPressed || dPressed != lastDPressed;

        if (keyStateChanged || activeCameraFrameCount <= 20 || activeCameraFrameCount % 60 == 0)
        {
            const auto [mouseX, mouseY] = Input::GetMousePosition();
            const glm::vec3 rot = m_Camera->GetRotation();
            std::cout << "[InputDebug][Editor] Camera update"
                << " frame=" << activeCameraFrameCount
                << " dt=" << dt
                << " speed=" << speed
                << " keys(WASD)=" << wPressed << aPressed << sPressed << dPressed
                << " mousePos=(" << mouseX << ", " << mouseY << ")"
                << " posBefore=(" << pos.x << ", " << pos.y << ", " << pos.z << ")"
                << " rot=(" << rot.x << ", " << rot.y << ", " << rot.z << ")"
                << std::endl;
        }

        lastWPressed = wPressed;
        lastSPressed = sPressed;
        lastAPressed = aPressed;
        lastDPressed = dPressed;

        if (wPressed) { pos += m_Camera->GetForward() * speed; moved = true; }
        if (sPressed) { pos -= m_Camera->GetForward() * speed; moved = true; }
        if (aPressed) { pos -= m_Camera->GetRight() * speed; moved = true; }
        if (dPressed) { pos += m_Camera->GetRight() * speed; moved = true; }

        if (moved)
        {
            m_Camera->SetPosition(pos);
            std::cout << "[InputDebug][Editor] Camera moved"
                << " posAfter=(" << pos.x << ", " << pos.y << ", " << pos.z << ")"
                << std::endl;
        }
    }

    void EditorLayer::CheckForHoveredEntity()
    {
        auto[mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        int mouseX = (int)mx;
        int mouseY = (int)my;

        if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
        {
            int pixelData = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
            m_HoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, m_ActiveScene.get());
        }
        else
        {
            m_HoveredEntity = {};
        }
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
            ImGuiID dockRightTopID = 0;
            ImGuiID dockRightBottomID = 0;

            ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Up, 0.08f, &dockTopID, &dockMainID);
            ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Down, 0.25f, &dockBottomID, &dockMainID);
            ImGui::DockBuilderSplitNode(dockMainID, ImGuiDir_Right, 0.25f, &dockRightID, &dockMainID);
            ImGui::DockBuilderSplitNode(dockRightID, ImGuiDir_Down, 0.45f, &dockRightBottomID, &dockRightTopID);

            ImGui::DockBuilderDockWindow("Top Panel", dockTopID);
            ImGui::DockBuilderDockWindow("Viewport", dockMainID);
            ImGui::DockBuilderDockWindow("Scene Hierarchy", dockRightTopID);
            ImGui::DockBuilderDockWindow("Settings", dockRightBottomID);
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

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(
            reinterpret_cast<void*>(static_cast<uintptr_t>(textureID)),
            viewportPanelSize,
            ImVec2{ 0, 1 },
            ImVec2{ 1, 0 }
        );

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
                if (ImGui::MenuItem("New Scene"))
                    NewScene();

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();
    }

    void EditorLayer::EndDockspace()
    {
        ImGui::End();
    }
}
