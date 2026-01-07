#pragma once

#include <string>
#include <vector>

#include "VUIElement.h"
#include "Vector2.h"

namespace VUI {
    struct VUIWindow {
        std::string Name;
        int ZIndex{};
        nlohmann::json properties;
        std::vector<VUIElement> Elements;
        ImVec2 Size;
    };
}
