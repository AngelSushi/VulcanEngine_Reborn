#pragma once
#include <memory>
#include <vector>

#include <ThemeAsset.h>
#include <Systems/VSystem.h>
#include <ImGuiRenderer.h>
#include <LogSystem.h>

#include <EditorUI/UIBuilder.h>
#include <EditorUI/UIRegistry.h>
#include <EditorUI/UIViewModel.h>
#include <EditorUI/UIWidget.h>

DECLARE_LOG_CATEGORY(EditorUI);

namespace VulcanEngine {

    struct EditorUIGlobals {
        UIRegistry Registry = UIRegistry::Create();
        std::optional<UIBuilder> Builder;

        UIViewModel GlobalVM;
        
        UIWidgetCache PrevCache;
        UIWidgetCache NextCache;
    };
    
    class VULCAN_ENGINE_API EditorSystem : public VSystem {
    public:
        
        static EditorSystem& Instance() {
            static EditorSystem instance;
            return instance;
        }

        EditorSystem();

        virtual void RegisterSystemWidgets();
        // VSystem interface
        void InitSystem() override;
        void StartSystem() override;
        void Iterate(float DeltaTime) override;

        void OnPreFrame() override;
        void OnPostFrame() override;

        ImGuiRenderer& GetGUIRenderer() const { return *GUIRenderer; }

    private:

        UIRenderContext MakeRenderContext();
        
        std::vector<std::unique_ptr<UIWidget>> EditorAssets;
        //TVector<UIAsset*> Themes;
        std::unique_ptr<ImGuiRenderer> GUIRenderer;

        EditorUIGlobals Globals;
    }; 
}
