#pragma once
#include "VUIElement.h"



namespace VUI {

    struct UILayout;

    class VUIRenderable {
    public:
        virtual void Render(const VUIElement& e,const UILayout& InParent) = 0;
        virtual ~VUIRenderable() = default;
    };
}
