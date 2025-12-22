#include <Renderables/VUICheckbox.h>

#include "VUIHelper.h"
#include <IRegistry.h>
#include <Types/VColor.h>

namespace VUI {
    
    void VUICheckbox::Render( const VUIElement& e,const UILayout& InParent) {
        auto label = VUIHelper::json_or<std::string>(e.Properties,"label","");
        auto bindName = VUIHelper::json_or<std::string>(e.Properties,"bind","");

        auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&bindName](const Binding& b) {
            return b.GetName() == bindName;
        });

        if (bindMethod) {
            auto color = VUIHelper::json_or<std::string>(e.Properties,"color","#FFFFFF");
            ImGui::PushStyleColor(ImGuiCol_CheckMark,VulcanEngine::VColor(color));
            std::string checkboxLabel = "##" + label;
            auto cursorPos = ImGui::GetCursorPos();
            bool& open = bindMethod->InvokeAs<bool>();
            ImGui::Checkbox(checkboxLabel.c_str(),&open);
            ImGui::SetCursorPos({cursorPos.x + 35.f,cursorPos.y});
            ImGui::Text(label.c_str());
            ImGui::PopStyleColor();
        }
        
        
    }
}
