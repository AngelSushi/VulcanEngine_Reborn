#pragma once
#include <Renderables/VUIRenderable.h>

namespace VUI {

    class VUIInputText : public VUIRenderable {
    public:
        void Render(const VUIElement& e,const UILayout& InParent) override;
    };
}
