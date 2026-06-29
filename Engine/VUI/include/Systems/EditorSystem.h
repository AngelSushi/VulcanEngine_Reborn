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

#include <EditorUI/Renderers/UIClaySDLRenderer.h>
#include <EditorUI/Backend/Clay/ClayBackend.h>
#include <EditorUI/Runtime/WidgetApplication.h>

#include "CoreAPI/VCore.h"
#include "CoreAPI/VWindow.h"


DECLARE_LOG_CATEGORY(EditorUI);

namespace VulcanEngine {

    struct EditorUIGlobals {
        UIRegistry Registry = UIRegistry::Create();
        std::optional<UIBuilder> Builder;

        UIViewModel GlobalVM;
        
        UIWidgetCache PrevCache;
        UIWidgetCache NextCache;

        ClayBackend* ClayBackend;

        WidgetApplication WApplication;
    };
    
    class VUI_API EditorSystem : public VSystem {
    public:
        
        static EditorSystem& Instance() {
            static EditorSystem instance;
            return instance;
        }

        EditorSystem();

        virtual void RegisterSystemWidgets();
        virtual void RegisterSystemScreens();
        // VSystem interface
        void InitSystem() override;
        void StartSystem() override;
        void Iterate(float DeltaTime) override;
        void Shutdown() override;

        void OnPreFrame() override;
        void OnPostFrame() override;

        static const EditorUIGlobals& GetGlobals() {
            return Globals;
        }

        // Not safe to make it public, use outside of EditorSystem with EventTrigger. 
        void AddWidget(const UINode& Node);
        
    private:
        UIRenderContext MakeRenderContext();
        
        std::vector<std::unique_ptr<UIWidget>> EditorAssets;
        //TVector<UIAsset*> Themes;

        const VWindow* Window;
        const Graphics::VRenderer* Renderer;

        static EditorUIGlobals Globals;
    }; 
}
