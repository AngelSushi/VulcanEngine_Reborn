
#include <Renderables/VUIGrid.h>

#include <ConsoleCommandSystem.h>
#include <Layout.h>
#include <VUIHelper.h>
#include <Renderables/VUIFactory.h>
#include <IRegistry.h>

#include <Systems/EditorSystem.h>

namespace VUI {
    VUIGrid::VUIGrid(const VUIElement& e) {
        auto items = VUIHelper::json_or<std::vector<nlohmann::json>>(e.Properties,"items",{});

        for (auto& item : items) {
            auto type = item.value("type","");
            auto className = item.value("class","");

            VUIElement childElement = {
                 !className.empty() ? className : type,
                 VUIHelper::json_or<std::string>(item,"label",""),
                 VUIHelper::json_or<std::string>(item,"bind",""),
                VUIHelper::json_or<std::string>(item,"visible",""),
                VUIHelper::json_or<std::string>(item,"onStateChanged",""),
                item
            };

            auto renderable = VUIFactory::Create(childElement);
            if (!renderable) {
                VLOG_WARN(EditorUI,"VUIGrid: Could not create renderable for item of type '{}'", type);
                continue;
            }
            
            Content.emplace_back(childElement, std::move(renderable));
        }
    }
    

    void VUIGrid::Render(const VUIElement& e,const  UILayout& InParent) {
        bool border = VUIHelper::json_or<bool>(e.Properties,"border",false);
        auto label = VUIHelper::json_or<std::string>(e.Properties,"label","GridRegion");
        
        UILayout gridLayout = UILayout::ParseLayout(e.Properties,ImGui::GetContentRegionAvail());

        int itemSizeX = 0;
        auto cursorPos = ImGui::GetCursorPos();
        
        ImGui::SetCursorPos({cursorPos.x + gridLayout.position.x,cursorPos.y +  gridLayout.position.y});
        
        ImGui::PushID(&e);
        ImGui::BeginChild(label.c_str(),{gridLayout.size.x,gridLayout.size.y},border,ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
        
        for (auto& [element, widget] : Content) {
            auto lLabel = VUIHelper::json_or<std::string>(element.Properties,"label","No Name");
            auto lBorder = VUIHelper::json_or<bool>(element.Properties,"border",false);
            auto fontScale = VUIHelper::json_or<float>(element.Properties,"fontScale",1.0f);

            UILayout itemLayout = UILayout::ParseLayout(element.Properties,{gridLayout.size.x,gridLayout.size.y},gridLayout);

            ImGui::SetWindowFontScale(fontScale);
        
            ImGui::SetCursorPos({itemLayout.position.x + itemSizeX,itemLayout.position.y});
            ImGui::BeginChild(lLabel.c_str(),{itemLayout.size.x,itemLayout.size.y},lBorder,ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

            widget->Render(element, gridLayout);
            
            ImGui::EndChild();
        
            ImGui::SetWindowFontScale(1.0f);
        
            itemSizeX += itemLayout.size.x + gridLayout.spacing.x + itemLayout.margin[1];
        }
        
        ImGui::EndChild();
        ImGui::PopID();
    }
}
