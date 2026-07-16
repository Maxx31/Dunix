#pragma once

#include "Scene.h"

namespace Dunix
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity inEntity, Scene* inScene);
        
        template<typename T, typename ... Args>
        T& AddComponent(Args&&... args)
        {
            return m_Scene->GetEnttRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }
        
        template<typename T>
        T& GetComponent()
        {
            return m_Scene->GetEnttRegistry().get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() const
        {
            return m_Scene->GetEnttRegistry().all_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            m_Scene->GetEnttRegistry().remove<T>(m_EntityHandle);
        }

        entt::entity GetHandle() const { return m_EntityHandle; }
        operator bool() const { return m_EntityHandle != entt::null && m_Scene != nullptr; }
    
    private:
        entt::entity m_EntityHandle{ entt::null };
        Scene* m_Scene = nullptr;
    };
}
