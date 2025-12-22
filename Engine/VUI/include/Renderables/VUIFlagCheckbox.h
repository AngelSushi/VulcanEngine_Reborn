#pragma once
#include "VUIRenderable.h"
#include <Types/Assets/UIAsset.h>

namespace VUI {

    class VUIFlagCheckbox : public VUIRenderable {
    public:
        void Render(const VUIElement& e,const UILayout& InParent) override;
    };
}
