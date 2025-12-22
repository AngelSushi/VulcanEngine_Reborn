#include "ThemeAsset.h"

#include <fmt/color.h>
#include <fmt/core.h>
#include <nlohmann/json.hpp>

#include "VUIHelper.h"
#include <Types/VColor.h>

#include "Reflection/ObjectManager.h"

namespace VUI {
    void ThemeAsset::ConstructJSON(const std::string_view& InPath) {
        // Load fonts

        std::filesystem::path Path{ InPath };
        AssetName = Path.stem().string();
        FilePath = std::move(Path.string()); // Reconstruct so we have to redo the replace
        std::replace(FilePath.begin(),FilePath.end(),'\\','/');
        
        for (auto& [key, value] : Description["colors"].items()) {
            VulcanEngine::VColor color(value.get<std::string>());
            Colors.push_back({VUIHelper::GetColorFlagByName(key),color});
       }
        
        for (auto& [key, value] : Description["vars"].items()) {
            if (value.is_array() && value.size() == 2) {
                StyleVars.push_back({VUIHelper::GetStyleVarByName(key),ImVec2(value[0].get<float>(),value[1].get<float>())});
            } else if (value.is_number_float()) {
                StyleVars.push_back({VUIHelper::GetStyleVarByName(key),value.get<float>()});
            } else if (value.is_number_integer()) {
                StyleVars.push_back({VUIHelper::GetStyleVarByName(key),static_cast<float>(value.get<int>())});
            }
        }


        DefaultFlags = Description.value("default_flags", nlohmann::json::object());
    }

    ThemeAsset* ThemeAsset::FromJson(const std::string& InJson) {
        auto Asset = VulcanCore::NewObject<ThemeAsset>();
        Asset->Description = nlohmann::json::parse(InJson);
        return Asset;
    }

    std::string ThemeAsset::ToJson() const {
        return Description.dump();
    }

    void ThemeAsset::Init() {
        ImGuiStyle& style = ImGui::GetStyle();

        for (auto& [col, colValue] : Colors) {
            style.Colors[col] = colValue;
        }
    }

    void ThemeAsset::Render(ImGuiWindowFlags& OutFlags) {
        OutFlags |= VUIHelper::json_or<bool>(DefaultFlags, "no_title_bar", false) ? ImGuiWindowFlags_NoTitleBar : 0;
        OutFlags |= VUIHelper::json_or<bool>(DefaultFlags, "no_resize", false) ? ImGuiWindowFlags_NoResize : 0;
        OutFlags |= VUIHelper::json_or<bool>(DefaultFlags,"no_move",false) ? ImGuiWindowFlags_NoMove : 0;
        OutFlags |= VUIHelper::json_or<bool>(DefaultFlags,"no_scrollbar",false) ? ImGuiWindowFlags_NoScrollbar : 0;
        OutFlags |= VUIHelper::json_or<bool>(DefaultFlags,"no_collapse",false) ? ImGuiWindowFlags_NoCollapse : 0;
        OutFlags |= VUIHelper::json_or<bool>(DefaultFlags,"always_auto_resize",false) ? ImGuiWindowFlags_AlwaysAutoResize : 0;

        for (auto& [var, varValue] : StyleVars) {
            if (std::holds_alternative<float>(varValue)) {
                ImGui::PushStyleVar(var, std::get<float>(varValue));
            } else if (std::holds_alternative<ImVec2>(varValue)) {
                ImGui::PushStyleVar(var, std::get<ImVec2>(varValue));
            }
        }

        
       // ImGuiStyle& style = ImGui::GetStyle();
       // style.FramePadding = {10,10};

    }

    void ThemeAsset::PostRender() {
        ImGui::PopStyleVar(StyleVars.size());
    }
}
