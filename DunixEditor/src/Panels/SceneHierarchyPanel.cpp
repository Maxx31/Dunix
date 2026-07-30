#include "SceneHierarchyPanel.h"

#include "Dunix/Scene/Scene.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

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
            for (auto& [id, entity] : m_Context->GetAllEntites())
            {
                DrawEntityNode(entity);
            }
            
            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            {
                m_SelectedEntity = {};
            }
            
            // Right-click on blank space
            if (ImGui::BeginPopupContextWindow(0, 1))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                    m_Context->CreateEntity("Empty Entity");

                ImGui::EndPopup();
            }
        }

        ImGui::End();
        
        ImGui::Begin("Properties");
        if (m_SelectedEntity)
        {
            //For now we can just show Transform or something temp
            //DrawComponents(m_SelectionContext);
        }

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
            | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        const auto entityId = static_cast<uint64_t>(entity.GetEntityId());
        ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<uintptr_t>(entityId)), flags, "%s", tag.c_str());
    	
        if (ImGui::IsItemClicked())
        {
            m_SelectedEntity = entity;
        }

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if (entityDeleted)
        {
            m_Context->DestroyEntity(&entity);
            if (m_SelectedEntity == entity)
            {
                m_SelectedEntity = {};
            }
        }
    }
}
