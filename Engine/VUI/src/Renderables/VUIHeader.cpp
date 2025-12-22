
#include <imgui_internal.h>
#include <Renderables/VUIHeader.h>


#include "Layout.h"
#include "UIUtils.h"
#include "VUIHelper.h"
#include <IRegistry.h>
#include <Entries/HeaderEntry.h>

namespace VUI {
    
    void VUIHeader::Render( const VUIElement& e,const UILayout& InParent) {
        auto bindMethod = VulcanEngine::BindingRegistry.FindIf([&](const Binding& b){
                return b.GetName() == e.Bind;
        });

        const auto& headerEntry = bindMethod ? bindMethod->InvokeAs<VulcanEngine::TVector<HeaderEntry>>() : VulcanEngine::TVector<HeaderEntry>{};
        
        auto gridLayout = UILayout::ParseLayout(e.Properties,ImGui::GetWindowSize());
        bool border = VUIHelper::json_or<bool>(e.Properties,"border",false);

        if (border) {
            ImGui::GetWindowDrawList()->AddRect(ImGui::GetCursorScreenPos(), { ImGui::GetCursorScreenPos().x + gridLayout.size.x , ImGui::GetCursorScreenPos().y + gridLayout.size.y }, IM_COL32(255,0,0,255));
        }

        auto headerColor = VUIHelper::json_or<std::string>(e.Properties,"Header","#FFFFFF");
        VulcanEngine::VColor headerCol = VulcanEngine::VColor(headerColor);
        
        auto framePadding = VUIHelper::json_or<std::pair<float,float>>(e.Properties,"FramePadding",{0.0f,0.0f});
        ImGuiStyle& style = ImGui::GetStyle();

        auto textColor = VUIHelper::json_or<std::string>(e.Properties,"Text","#FFFFFF");
        VulcanEngine::VColor textCol = VulcanEngine::VColor(textColor);

        ImVec2 oldPadding = style.FramePadding;
        style.FramePadding = {framePadding.first,framePadding.second};
        
        ImGui::PushStyleColor(ImGuiCol_Header,headerCol);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered,headerCol.Lighten(0.3f));
        
        ImGui::SetCursorPos({ImGui::GetCursorPos().x + gridLayout.margin[3],ImGui::GetCursorPos().y + gridLayout.margin[0]});
        ImGui::BeginChild("##HeaderRegion", {gridLayout.size.x, gridLayout.size.y}, border);

        for (auto entry : headerEntry) { // Make sure to copy the entry to avoid dangling references
            if (ImGui::CollapsingHeader(entry.HeaderName.c_str())) {
                size_t i = 0;
                for (auto& [propValue,obj] : entry.Properties) {
                    bool changed = false;

                    auto cursorPos = ImGui::GetCursorPos();

                    ImGui::SetCursorPos({cursorPos.x + gridLayout.margin[3],cursorPos.y + gridLayout.margin[0]});
                    ImGui::TextColored(textCol,"%s", propValue->GetName().c_str());

                    ImGui::SetCursorPos({ ImGui::GetCursorPos().x + 150.0f,cursorPos.y + gridLayout.margin[0]});
                    UIProperty::DrawClassProperty(obj, propValue, changed);
                    
                    if (i == entry.Properties.size() - 1) {
                        ImGui::Dummy({gridLayout.margin[1],gridLayout.margin[2]});
                    }
                    
                    i++;
                }
            }
        }
          
        
        ImGui::EndChild();

        ImGui::PopStyleColor(2);
        style.FramePadding = oldPadding;
    
    }
}
