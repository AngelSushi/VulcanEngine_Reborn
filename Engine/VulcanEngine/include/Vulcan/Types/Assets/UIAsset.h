#pragma once
#include <nlohmann/json.hpp>

#include <VUIWindow.h>

#include <LogSystem.h>
#include <Types/Assets/VAsset.h>

#include <Renderables/VUIRenderable.h>

#include <EditorUI/UIWidget.h>
#include <EditorUI/UIBuilder.h>

#include <EditorUI/UIWidgetCache.h>


DECLARE_LOG_CATEGORY(UI);
namespace VulcanEngine {
    
    class UIAsset : public VAsset {
        
    public:
        UIAsset();
        
        static UIAsset* FromJson(const std::string& InJson);
        std::string ToJson() const override;

        void ConstructJson(const std::string_view& InPath) override;
        void Show();
        void Hide();


        const UIWidget* Root() const { return OutRoot.get(); }

        void Build(const UIRegistry& InRegistry,const UIBuilder& InBuilder);
    private:

        void BuildFromNode(const UINode& RootNode);
        std::unique_ptr<UIWidget> OutRoot;
        UINode OutNode;

        UIWidgetCache PrevCache;
        UIWidgetCache Cache;
    };
}
