#include "dxpch.h"
#include "SaveManager.h"

#include "Dunix/Scene/Scene.h"

namespace Dunix
{
    using json = nlohmann::json;
    
    SaveManager* SaveManager::m_Instance = nullptr;
    
    SaveManager::SaveManager()
    {
        m_Instance = this;
    }

    SaveManager::~SaveManager()
    {
        m_Instance = nullptr;
    }

    json SaveManager::ConvertSceneToJson(SharedPtr<Scene> Scene)
    {
        //Here we pass all the info from scene: Entities and name for now;
        json sceneData;
        sceneData["Entities"] = json::array();
        sceneData["Name"] = "Test";
        
        return sceneData;
    }

    SharedPtr<Scene> SaveManager::ConvertJsonToScene(nlohmann::json Json)
    {
        //Here we take json file and convert it to scene, filling entities and name
        SharedPtr<Scene>NewScene = std::make_shared<Scene>();
        
        return NewScene;
    }
}
