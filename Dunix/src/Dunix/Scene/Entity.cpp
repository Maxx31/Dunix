#include "dxpch.h"
#include "Entity.h"

namespace Dunix
{
    Entity::Entity(entt::entity inEntity, Scene* inScene)
        : m_EntityHandle(inEntity), m_Scene(inScene)
    {
    }
}
