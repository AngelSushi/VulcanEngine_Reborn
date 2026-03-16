#pragma once
#include <CoreAPI/precomp.h>

#include <ThemeAsset.h>
#include <Systems/VSystem.h>
#include <LogSystem.h>

#include <EditorUI/Core/UIBuilder.h>
#include <EditorUI/Core/UIRegistry.h>
#include <EditorUI/Runtime/UIViewModel.h>
#include <EditorUI/Core/UIWidget.h>
#include <EditorUI/Runtime/UIRenderContext.h>

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

    private:

        UIRenderContext MakeRenderContext();
        
        std::vector<std::unique_ptr<UIWidget>> EditorAssets;
        //TVector<UIAsset*> Themes;

        EditorUIGlobals Globals;
    }; 
}
