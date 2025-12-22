
#include "Renderables/VUISeparator.h"

#include "Layout.h"
#include <Types/VColor.h>
#include <Types/Assets/UIAsset.h>

namespace VUI {
    
    void VUISeparator::Render(const VUIElement& e,const UILayout& InParent) {

        UILayout layout = UILayout::ParseLayout(e.Properties,ImGui::GetContentRegionAvail());
        
        auto thickness = VUIHelper::json_or<float>(e.Properties,"thickness",1.f);
        auto color = VUIHelper::json_or<std::string>(e.Properties,"color","#FFFFFF");
        
        ImVec2 cursorScreen = ImGui::GetCursorScreenPos();
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        
        VulcanEngine::VColor convertedColor = VulcanEngine::VColor(color);
        
        float startX = cursorScreen.x  + (layout.margin[3] - layout.size.x * 0.5f);
        float startY = cursorScreen.y + (layout.margin[0] - layout.size.y * 0.5f);
        float barWidth = layout.size.x;
        float barHeight = thickness;

        drawList->AddRectFilled(ImVec2(startX, startY),ImVec2(startX + barWidth, startY + barHeight),IM_COL32(convertedColor.R() * 255, convertedColor.G() * 255, convertedColor.B() * 255, convertedColor.A() * 255));
        
        ImGui::Dummy({0,layout.margin[2]});
    }
}
