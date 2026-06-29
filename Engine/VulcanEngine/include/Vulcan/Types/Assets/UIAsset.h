#pragma once
#include <CoreAPI/precomp.h>
#include <nlohmann/json.hpp>


#include <LogSystem.h>
#include <Types/Assets/VAsset.h>

//#include <EditorUI/Core/UIWidget.h>

//#include <EditorUI/Core/UIWidgetCache.h>


namespace VulcanEngine {

    DECLARE_LOG_CATEGORY(UI);
    
    class UIAsset : public VAsset {
        
    public:
        UIAsset();
        
        static UIAsset* FromJson(const std::string& InJson);
        std::string ToJson() const override;

        void ConstructJson(const std::string_view& InPath) override;
        void Show();
        void Hide();


  //      const UIWidget* Root() const { return OutRoot.get(); }

       // void Build(const UIRegistry& InRegistry,const UIBuilder& InBuilder);
    private:

    /*    void BuildFromNode(const UINode& RootNode);
        std::unique_ptr<UIWidget> OutRoot;
        UINode OutNode;

        UIWidgetCache PrevCache;
        UIWidgetCache Cache;
    */
    };
}
