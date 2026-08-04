#pragma once

#include "Components.h"
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
        T& GetComponent() const
        {
            return m_Scene->GetEnttRegistry().get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent() const
        {
            return m_Scene->GetEnttRegistry().all_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent() const
        {
            m_Scene->GetEnttRegistry().remove<T>(m_EntityHandle);
        }
        
        UUID GetEntityID() const
        {
            return GetComponent<IDComponent>().ID;
        }
        
        const std::string& GetEntityName() const
        {
            return GetComponent<TagComponent>().Name;
        }
        
        bool operator==(const Entity& entity) const
        {
            return m_EntityHandle == entity.m_EntityHandle && m_Scene == entity.m_Scene;
        }

        bool operator!=(const Entity& entity) const
        {
            return !(*this == entity);
        }

        entt::entity GetHandle() const { return m_EntityHandle; }
        operator bool() const { return m_EntityHandle != entt::null && m_Scene != nullptr; }
    
    private:
        entt::entity m_EntityHandle{ entt::null };
        Scene* m_Scene = nullptr;
    };
}
