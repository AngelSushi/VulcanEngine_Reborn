#pragma once
#include "IRequestRenderer.h"
#include "ThemeAsset.h"
#include "UIRequest.h"

namespace VUI {
    class IRequestRenderer;

    class UIRequestRenderer {
    public:
        static UIRequestRenderer& Instance() {
            static UIRequestRenderer instance;
            return instance;
        }

        void RegisterRenderer(UIRequestType InType, std::unique_ptr<IRequestRenderer> InRenderer) {
            Renderers[InType] = std::move(InRenderer);
        }

        void Render(const UIRequest& InRequest) {
            auto it = Renderers.find(InRequest.RequestType);
            if (it != Renderers.end()) {
                it->second->Render(InRequest);
            }
        }

    private:
        std::unordered_map<UIRequestType,std::unique_ptr<IRequestRenderer>> Renderers;
    };
}
