#include "SceneHierarchyPanel.h"

#include "Dunix/Scene/Components.h"
#include "Dunix/Scene/Scene.h"

#include <imgui/imgui.h>

#include <array>
#include <cstring>

namespace Dunix
{
    SceneHierarchyPanel::SceneHierarchyPanel(const SharedPtr<Scene>& scene)
    {
        SetNewContext(scene);
    }

    void SceneHierarchyPanel::SetNewContext(const SharedPtr<Scene>& InScene)
    {
        m_Context = InScene;
        m_SelectedEntity = {};
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        if (m_Context)
        {
            m_EntityToDelete = {};
            m_EntityToDuplicate = {};

            if (ImGui::Button("Create Entity"))
                m_SelectedEntity = m_Context->CreateEntity("Empty Entity");

            ImGui::Separator();

            auto view = m_Context->GetEnttRegistry().view<IDComponent, TagComponent>();
            for (auto entityHandle : view)
                DrawEntityNode({ entityHandle, m_Context.get() });

            if (m_EntityToDuplicate)
                m_SelectedEntity = m_Context->DuplicateEntity(m_EntityToDuplicate);

            if (m_EntityToDelete)
            {
                if (m_SelectedEntity == m_EntityToDelete)
                    m_SelectedEntity = {};

                m_Context->DestroyEntity(m_EntityToDelete);
            }

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsWindowHovered() && !ImGui::IsAnyItemHovered())
                m_SelectedEntity = {};

            if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    m_SelectedEntity = m_Context->CreateEntity("Empty Entity");

                ImGui::EndPopup();
            }
        }

        ImGui::End();

        ImGui::Begin("Settings");

        if (m_SelectedEntity)
            DrawComponents(m_SelectedEntity);
        else
            ImGui::TextDisabled("No entity selected.");

        ImGui::End();
    }

    void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
    {
        m_SelectedEntity = entity;
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Name;

        ImGuiTreeNodeFlags flags = ((m_SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0)
            | ImGuiTreeNodeFlags_OpenOnArrow
            | ImGuiTreeNodeFlags_Leaf
            | ImGuiTreeNodeFlags_NoTreePushOnOpen
            | ImGuiTreeNodeFlags_SpanAvailWidth;

        const uint64_t entityID = static_cast<uint64_t>(entity.GetEntityID());
        ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uintptr_t>(entityID)), flags, "%s", tag.c_str());

        if (ImGui::IsItemClicked())
            m_SelectedEntity = entity;

        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Duplicate Entity"))
                m_EntityToDuplicate = entity;

            if (ImGui::MenuItem("Delete Entity"))
                m_EntityToDelete = entity;

            ImGui::EndPopup();
        }
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>().Name;
            std::array<char, 256> buffer{};
            std::strncpy(buffer.data(), tag.c_str(), buffer.size() - 1);

            if (ImGui::InputText("Name", buffer.data(), buffer.size()))
                tag = buffer.data();
        }

        if (entity.HasComponent<TransformComponent>())
        {
            auto& transform = entity.GetComponent<TransformComponent>();

            ImGui::SeparatorText("Transform");
            ImGui::DragFloat3("Position", &transform.Position.x, 0.1f);
            ImGui::DragFloat3("Rotation", &transform.Rotation.x, 0.1f);
            ImGui::DragFloat3("Scale", &transform.Scale.x, 0.1f);
        }
    }
}
