#pragma once

#include <Renderables/VUIRenderable.h>

namespace VUI {

    class VUICheckbox : public VUIRenderable {
    public:
        void Render(const VUIElement& e,const UILayout& InParent) override;
    };
}
