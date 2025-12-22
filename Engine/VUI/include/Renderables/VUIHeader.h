#pragma once

#include "VUIRenderable.h"

namespace VUI {

    class VUIHeader : public VUIRenderable {
    public:
        void Render(const VUIElement& e,const UILayout& InParent) override;

    };
}
