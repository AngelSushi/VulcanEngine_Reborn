
#include "Renderables/VUITextureButton.h"

#include "Layout.h"
#include "VUIHelper.h"
#include <IRegistry.h>

#include "ResourceManager.h"

namespace VUI {

    void VUITextureButton::Render(const VUIElement& e,const UILayout& InParent) {

        UILayout itemLayout = UILayout::ParseLayout(e.Properties,{InParent.size.x,InParent.size.y},InParent);

        auto bindName = VUIHelper::json_or<std::string>(e.Properties,"bind","");
        auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&bindName](const Binding& b) {
            return b.GetName() == bindName;
        });
            
        auto color = VUIHelper::json_or<std::string>(e.Properties,"color","#FFFFFF");
        ImGui::PushStyleColor(ImGuiCol_Button,VulcanEngine::VColor(color));
    //    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,VulcanEngine::VColor(color).Lighten(0.15f)); // Lighten 
    //    ImGui::PushStyleColor(ImGuiCol_ButtonActive,VulcanEngine::VColor(color).Darken(0.15f)); // Darken

        auto label = "##btn_" + std::to_string(reinterpret_cast<uintptr_t>(&e));

        auto textures = VUIHelper::json_or<nlohmann::json>(e.Properties,"textures",{});

        auto normalTexture = VUIHelper::json_or<std::string>(textures,"normal","");
        auto normalTexturePtr = VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName(normalTexture);

        auto hoveredTexture = VUIHelper::json_or<std::string>(textures,"hover","");
        auto hoveredTexturePtr = VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName(hoveredTexture);
        
        if (!CurrentTextureID) {
            CurrentTextureID = normalTexturePtr->GetTexture();
        }
        
        if (ImGui::ImageButton(CurrentTextureID,{itemLayout.size.x,itemLayout.size.y})) {
            if (bindMethod) {
                bindMethod->Invoke();
            }
        }

        if (ImGui::IsItemHovered()) {
            CurrentTextureID = hoveredTexturePtr->GetTexture();
        }
        else {
            CurrentTextureID = normalTexturePtr->GetTexture();
        }
            
        ImGui::PopStyleColor(1);
    }
}
