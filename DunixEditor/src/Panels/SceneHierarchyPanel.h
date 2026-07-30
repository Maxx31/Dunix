#pragma once
#include "Dunix/Scene/Entity.h"

namespace Dunix
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const SharedPtr<Scene>& scene);
        
        void SetNewContext(const SharedPtr<Scene>& InScene);
        
        void OnImGuiRender();
        
        Entity GetSelectedEntity() const { return m_SelectedEntity; }
        void SetSelectedEntity(Entity entity);
        
    private:
        template<typename T>
        void DisplayAddComponentEntry(const std::string& entryName);
	
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);
        
    private:
        SharedPtr<Scene> m_Context;
        Entity m_SelectedEntity;
    };
}
