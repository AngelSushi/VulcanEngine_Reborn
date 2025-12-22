#pragma once
#include <nlohmann/json.hpp>

#include "VUIRenderable.h"
#include <Types/Assets/UIAsset.h>

namespace VUI {
    struct UILayout;

    class VUIGrid : public VUIRenderable {
    public:
        VUIGrid(const VUIElement& e);
        void Render( const VUIElement& e,const UILayout& InParent) override;

    private:
        std::vector<std::pair<VUIElement,std::unique_ptr<VUIRenderable>>> Content{};
    };
}
