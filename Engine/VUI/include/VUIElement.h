#pragma once
#include <nlohmann/json.hpp>

namespace VUI {
    struct VUIElement {
        VUIElement(const std::string& InType, const std::string& InLabel,const std::string& InBind, const std::string& InVisibilityBind,const std::string& InSelect,const nlohmann::json& Properties)
        : Type(InType), Label(InLabel),Bind(InBind),VisibilityBind(InVisibilityBind), OnStateChanged(InSelect), Properties(Properties) {}
        
        std::string Type;
        std::string Label;
        std::string Bind;
        std::string VisibilityBind;
        std::string OnStateChanged;
        nlohmann::json Properties;

        //std::vector<VUIElement> Children;
    };
}
