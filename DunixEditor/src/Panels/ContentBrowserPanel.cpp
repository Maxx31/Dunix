#include "ContentBrowserPanel.h"

#include <string>

#include "Dunix/Managers/ProjectManager.h"
#include "imgui/imgui.h"

namespace Dunix
{
    ContentBrowserPanel::ContentBrowserPanel()
    {
    }

    void ContentBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("Content Browser");
        
        const std::string& projectPath = ProjectManager::Get().GetProjectPath();
        
        //Either here to go throw everything or ask Project manager to give us a list of everything
        
        if (ImGui::BeginPopupContextWindow(nullptr, ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            if (ImGui::MenuItem("Create Empty Folder"))
            {
                ProjectManager::Get().CreateFolder("Test Folder");
            }

            ImGui::EndPopup();
        }
        
        ImGui::End();
    }
}
