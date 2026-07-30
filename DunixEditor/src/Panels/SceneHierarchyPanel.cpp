#include "SceneHierarchyPanel.h"

#include "imgui/imgui.h"

namespace Dunix
{
    SceneHierarchyPanel::SceneHierarchyPanel(const SharedPtr<Scene>& scene)
    {
        SetNewContext(scene);
    }

    void SceneHierarchyPanel::SetNewContext(const SharedPtr<Scene>& InScene)
    {
        SetNewContext(InScene);
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        
        //Need to go throw all the entities from our scene and display them in the list
        ImGui::Begin("Scene Hierarchy");

        if (m_Context)
        {
        }

        ImGui::End();
        
        ImGui::Begin("Properties");
        if (m_SelectionContext)
        {
            DrawComponents(m_SelectionContext);
        }

        ImGui::End();
    }

    void SceneHierarchyPanel::SetSelectedEntity(Entity entity)
    {
        
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
    }
    
    template <typename T>
    void SceneHierarchyPanel::DisplayAddComponentEntry(const std::string& entryName)
    {
        
    }

    
}