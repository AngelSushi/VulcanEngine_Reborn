#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UIValue.h>

#include "JsonHelper.h"


// Represents data read in the .json file for a UI node.
struct UINode {
    std::string Redirect;
    
    std::string Type;
    std::string Id;
    int WindowIndex = 0;

    std::vector<UINode> Children;

    std::unordered_map<std::string, UIValue> Properties;
    std::unordered_map<std::string,std::string> Bindings;
    std::unordered_map<std::string,std::string> Events;

    // For style, we can either have a string (for a theme file directly) or a map of style properties.
    //std::variant<std::string,std::unordered_map<std::string,std::string>> Style;
    std::string Style;

    UIValue TryPropValue(const std::string& Key) {
        if (Properties.contains(Key)) {
            return Properties[Key];
        }

        return UIValue();
    }
    
    std::tuple<UIValue,bool> TryProp(const std::string& Key) {
        if (Properties.contains(Key)) {
            return std::make_tuple(Properties[Key], true);
        }

        return std::make_tuple(UIValue(), false);
    }

    static void Merge(UINode& Base, UINode& Override) {
        for (auto& [Key,Value] : Base.Properties) {
            Override.Properties[Key] = Value;
        }

        if (Override.Children.size() > 0) {
            // Never clear the children of the override, we just append the children of the base to the override - maybe we can change this behavior in the future if we want to clear the base children
            //Base.Children.clear();
            for (auto& LocalChild : Override.Children) {
                Base.Children.push_back(LocalChild);
            }
        }
    }
};

// Maybe useless cause we never change the structure of the UINode, but we can keep it for future changes
inline void to_json(nlohmann::json& Object, const UINode& Node) {
    Object = nlohmann::json {
        {"Redirect", Node.Redirect},
        {"Type", Node.Type},
        {"Id", Node.Id},
           {"WindowIndex", Node.WindowIndex},
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
    if (Object.contains("Redirect") && Object["Redirect"].is_string()) {
        Node.Redirect = Object["Redirect"].get<std::string>();
    }

    if (Object.contains("Type") && Object["Type"].is_string()) {
        Node.Type = Object.at("Type");
    }

    if (Object.contains("Id") && Object["Id"].is_string()) {
        Node.Id = Object.at("Id");
    }

    if (Object.contains("WindowIndex") && Object["WindowIndex"].is_number_integer()) {
        Node.WindowIndex = Object.at("WindowIndex");
    }
    else {
        Node.WindowIndex = 0; // Default value if not present
    }
    
    if (Object.contains("Children") && Object["Children"].is_array()) {
        Node.Children = Object.at("Children");
    }

    if (Object.contains("Bindings") && Object["Bindings"].is_object()) {
        Node.Bindings = Object.at("Bindings");
    }

    if (Object.contains("Events") && Object["Events"].is_object()) {
        Node.Events = Object.at("Events");
    }

    if (Object.contains("Style") && Object["Style"].is_string()) {
        Node.Style = Object.at("Style");
    }

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