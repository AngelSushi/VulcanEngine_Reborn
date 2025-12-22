
#include "Renderables/VUIButton.h"

#include "Layout.h"
#include "VUIHelper.h"
#include <IRegistry.h>

namespace VUI {
    
    void VUIButton::Render(const VUIElement& e,const UILayout& InParent) {

        auto label = VUIHelper::json_or<std::string>(e.Properties,"label","No Name");
        UILayout itemLayout = UILayout::ParseLayout(e.Properties,{InParent.size.x,InParent.size.y},InParent);

        auto bindName = VUIHelper::json_or<std::string>(e.Properties,"bind","");
        auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&bindName](const Binding& b) {
            return b.GetName() == bindName;
        });
            
        auto color = VUIHelper::json_or<std::string>(e.Properties,"color","#FFFFFF");
        ImGui::PushStyleColor(ImGuiCol_Button,VulcanEngine::VColor(color));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,VulcanEngine::VColor(color).Lighten(0.15f)); // Lighten 
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,VulcanEngine::VColor(color).Darken(0.15f)); // Darken

        if (ImGui::Button(label.c_str(),{itemLayout.size.x,itemLayout.size.y})) {
            if (bindMethod) {
                bindMethod->Invoke();
            }
        }
            
        ImGui::PopStyleColor(3);
    }
}
