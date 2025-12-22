#pragma once
#include <optional>
#include <string>
#include <vector>

#include "VUIElement.h"
#include "ThemeAsset.h"
#include "Vector2.h"

namespace VUI {
    struct VUIWindow {
        std::string Name;
        int ZIndex{};
        nlohmann::json properties;
        ThemeAsset Theme{};
        std::vector<VUIElement> Elements;
        ImVec2 Size;
    };
}
