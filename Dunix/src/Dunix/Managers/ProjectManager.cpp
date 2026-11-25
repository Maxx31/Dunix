#include "dxpch.h"
#include "ProjectManager.h"

#include <filesystem>

using directory_iterator = std::filesystem::directory_iterator;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

namespace Dunix
{
    ProjectManager* ProjectManager::m_Instance = nullptr;

    ProjectManager::ProjectManager()
    {
        m_Instance = this;
    }

    ProjectManager::~ProjectManager()
    {
        m_Instance = nullptr;
    }

    std::vector<std::string> ProjectManager::GetAllProjects()
    {
        std::vector<std::string> projects;
        for (const auto& dirEntry : directory_iterator(std::filesystem::current_path()))
            projects.push_back(dirEntry.path().string());
        return projects;
    }
    
    void ProjectManager::CreateProjectInLocalPathWithName(std::string name, std::string projectPath)
    {
        if (projectPath == " ")
        {
            if (std::filesystem::create_directory(name) == false)
            {
                DX_ERROR("Create directory for the project failed");
            }
        }
        else
        {
            //Create project in this specific path
        }
        
        m_ProjectPath = name;
        m_ProjectSelected = true;
    }

    void ProjectManager::OpenProjectWithLocalPath(const std::string& path)
    {
        m_ProjectPath = path;
        m_ProjectSelected = true;
    }

    std::string ProjectManager::GetProjectFiles()
    {
        //Here need to check if what type of object it is and parse it
        std::vector<std::string> projects;
        for (const auto& dirEntry : directory_iterator(std::filesystem::current_path()))
            projects.push_back(dirEntry.path().string());
        
        return "";
    }

    void ProjectManager::SetProjectPath(const std::string& inProjectPath)
    {
        m_ProjectPath = inProjectPath; 
        m_ProjectSelected = true;
    }

    void ProjectManager::CreateFolder(const std::string& inName)
    {
        if (std::filesystem::create_directory(inName) == false)
        {
            DX_ERROR("Create new folder failed");
        }
    }
}
