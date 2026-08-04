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
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

    private:
        SharedPtr<Scene> m_Context;
        Entity m_SelectedEntity;
        Entity m_EntityToDelete;
        Entity m_EntityToDuplicate;
    };
}
