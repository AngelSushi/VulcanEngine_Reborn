#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UIValue.h>


// Represents data read in the .json file for a UI node.
struct UINode {

    std::string Type;
    std::string Id;

    std::vector<UINode> Children;

    std::unordered_map<std::string, UIValue> Properties;
    std::unordered_map<std::string,std::string> Bindings;
    std::unordered_map<std::string,std::string> Events;

    // For style, we can either have a string (for a theme file directly) or a map of style properties.
    //std::variant<std::string,std::unordered_map<std::string,std::string>> Style;
    std::string Style;
};

inline void to_json(nlohmann::json& Object, const UINode& Node) {
    Object = nlohmann::json {
        {"Type", Node.Type},
        {"Id", Node.Id},
        {"Children", Node.Children},
        {"Bindings", Node.Bindings},
        {"Events", Node.Events},
        {"Style", Node.Style}
    };

   /* nlohmann::json Properties;
    for (const auto& [Key, Value] : Node.Properties) {
        if (Value.Is<std::string>()) {
            Properties[Key] = Value.Get<std::string>();
        } else if (Value.Is<float>()) {
            Properties[Key] = Value.Get<float>();
        } else if (Value.Is<bool>()) {
            Properties[Key] = Value.Get<bool>();
        } else if (Value.Is<int>()) {
            Properties[Key] = Value.Get<int>();
        }
    }

    Object["Properties"] = Properties;*/
}

inline void from_json(const nlohmann::json& Object, UINode& Node)
{
    Node.Type = Object.at("Type");
    Node.Id = Object.at("Id");
    Node.Children = Object.at("Children");
    Node.Bindings = Object.at("Bindings");
    Node.Events = Object.at("Events");
    Node.Style = Object.at("Style");

  /*  const auto& Properties = Object.at("Properties");
    for (auto it = Properties.begin(); it != Properties.end(); ++it) {
        const std::string& Key = it.key();
        const auto& Value = it.value();

        if (Value.is_string()) {
            Node.Properties[Key] = Value.get<std::string>();
        } else if (Value.is_number_float()) {
            Node.Properties[Key] = Value.get<float>();
        } else if (Value.is_boolean()) {
            Node.Properties[Key] = Value.get<bool>();
        } else if (Value.is_number_integer()) {
            Node.Properties[Key] = Value.get<int>();
        }
    }*/
}