#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "Vector2.h"
#include "EditorUI/Backend/Clay/ClayHelper.h"

// Maybe have to change the folder later for more general usage, but for now just put it here.

using PropertyParser = std::function<bool(const nlohmann::json&, std::unordered_map<std::string,UIValue>& Properties, const std::string&)>;

template<typename T>
PropertyParser MakeParser()
{
    return [] (const nlohmann::json& JsonObject,std::unordered_map<std::string,UIValue>& Properties, const std::string& Key)  {
        try {
            Properties[Key] = JsonObject.get<T>();
            return true;
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            return false;
        }
    };
}

inline static const std::vector<PropertyParser> Parsers = {
    MakeParser<ClaySize>(),
    MakeParser<VMath::Vector2f>(),
};