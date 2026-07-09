#pragma once

#include "Scene.h"

namespace Dunix
{
    class Entity
    {
    public:
        Entity(entt::entity inEntity, Scene* inScene);
        
        template<typename T, typename ... Args>
        T& AddComponent(Args&& args)
        {
            T& component = m_Scene->GetEnttRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }
        
        template<typename T, typename ... Args>
        T& GetComponent(Args&& args)
        {
            return m_Scene->GetEnttRegistry().get<T>(m_EntityHandle);
        }
    
    private:
        entt::entity m_EntityHandle{ entt::null };
        Scene* m_Scene = nullptr;
    };
}
