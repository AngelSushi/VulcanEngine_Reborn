#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UIValue.h>

#include <IO/JSON/JsonSerializer.h>

#include "JsonHelper.h"


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

    UIValue TryProp(const std::string& Key) {
        return Properties.contains(Key) ? Properties[Key] : UIValue();
    }
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

    nlohmann::json Properties;
    for (const auto& [Key, Value] : Node.Properties) {
        if (Value.Is<std::string>()) {
            Properties[Key] = Value.Get<std::string>();
        } else if (Value.Is<float>()) {
            Properties[Key] = Value.Get<float>();
        } else if (Value.Is<bool>()) {
            Properties[Key] = Value.Get<bool>();
        } else if (Value.Is<int>()) {
            Properties[Key] = Value.Get<int>();
        } else if (Value.Is<VMath::Vector2f>()) {
            Properties[Key] = Value.Get<VMath::Vector2f>();
        }
        /*else if (Value.Is<ClaySize>()) {
            Properties[Key] = Value.Get<ClaySize>();
        }*/
    }

    Object["Properties"] = Properties;
}

inline void from_json(const nlohmann::json& Object, UINode& Node)
{
    Node.Type = Object.at("Type");
    Node.Id = Object.at("Id");
    Node.Children = Object.at("Children");
    Node.Bindings = Object.at("Bindings");
    Node.Events = Object.at("Events");
    Node.Style = Object.at("Style");

    const auto& Properties = Object.at("Properties");
    for (auto it = Properties.begin(); it != Properties.end(); ++it) {
        const std::string& Key = it.key();
        const auto& JsonProperty = it.value();

        if (JsonProperty.is_string()) {
            Node.Properties[Key] = JsonProperty.get<std::string>();
        } else if (JsonProperty.is_number_float()) {
            Node.Properties[Key] = JsonProperty.get<float>();
        } else if (JsonProperty.is_boolean()) {
            Node.Properties[Key] = JsonProperty.get<bool>();
        } else if (JsonProperty.is_number_integer()) {
            Node.Properties[Key] = JsonProperty.get<int>();
        } else if (JsonProperty.is_array()) {
            // Modify after for a most generic system
            if (JsonProperty.size() == 2 && JsonProperty[0].is_number() && JsonProperty[1].is_number()) {
                Node.Properties[Key] = JsonProperty.get<VMath::Vector2f>();
            }
        } else if (JsonProperty.is_object()) { 
            for (auto& Parser : Parsers) {
                if (Parser(JsonProperty, Node.Properties, Key)) {
                    break;
                }
            }
        }
    }
}