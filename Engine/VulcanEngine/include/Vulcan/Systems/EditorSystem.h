#pragma once
#include <memory>
#include <vector>

#include <ThemeAsset.h>
#include <Systems/VSystem.h>
#include <ImGuiRenderer.h>
#include <LogSystem.h>
#include <Types/Assets/UIAsset.h>

#include "TVector.h"

DECLARE_LOG_CATEGORY(EditorUI);

namespace VulcanEngine {
    class VULCAN_ENGINE_API EditorSystem : public VSystem {
    public:
        
        static EditorSystem& Instance() {
            static EditorSystem instance;
            return instance;
        }

        EditorSystem();
        
        // VSystem interface
        void InitSystem() override;
        void StartSystem() override;
        void Iterate(float DeltaTime) override;

        void OnPreFrame() override;
        void SetupDockspace();
        void OnPostFrame() override;

        ImGuiRenderer& GetGUIRenderer() const { return *GUIRenderer; }

    private:
        TVector<UIAsset*> EditorAssets;
        TVector<UIAsset*> Themes;
        std::unique_ptr<ImGuiRenderer> GUIRenderer;
    };
}
