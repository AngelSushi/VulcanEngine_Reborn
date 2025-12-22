#pragma once

#include <Renderables/VUIRenderable.h>

#include "TVector.h"
#include "Reflection/VObject.h"


namespace VUI {
    
    class VUICombo : public VUIRenderable {
    public:
        void Render(const VUIElement& e,const UILayout& InParent) override;
    private:
        std::pair<size_t,std::string> Selected;

        void BuildPreview(VulcanEngine::TVector<std::unique_ptr<VulcanCore::ReflectionBase>>& Objects, std::string& OutPreview);
    };
}
