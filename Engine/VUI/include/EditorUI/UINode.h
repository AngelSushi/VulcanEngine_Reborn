#pragma once
#include <CoreAPI/precomp.h>

// Represents data read in the .json file for a UI node.
struct UINode {

    std::string Type;
    std::string Id;

    std::vector<UINode> Children;

    std::unordered_map<std::string, std::string> Properties;
    std::unordered_map<std::string,std::string> Bindings;
    std::unordered_map<std::string,std::string> Events;

    // For style, we can either have a string (for a theme file directly) or a map of style properties.
    std::variant<std::string,std::unordered_map<std::string,std::string>> Style;
};