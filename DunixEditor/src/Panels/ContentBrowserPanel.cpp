#include "ContentBrowserPanel.h"

#include "imgui/imgui.h"

namespace Dunix
{
    ContentBrowserPanel::ContentBrowserPanel()
    {
    }

    void ContentBrowserPanel::OnImGuiRender()
    {
        ImGui::Begin("Content Browser");
        
        ImGui::End();
    }
}
