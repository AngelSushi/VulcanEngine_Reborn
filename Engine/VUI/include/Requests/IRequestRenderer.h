#pragma once
#include <optional>
#include <string>
#include <vector>

#include "VUIElement.h"
#include "ThemeAsset.h"
#include "UIRequest.h"
#include "Vector2.h"

namespace VUI {
    
    class IRequestRenderer {
    public:
        virtual void Render(const UIRequest& InRequest) = 0;
        virtual ~IRequestRenderer() = default;
    };
}
