#pragma once
#include <CoreAPI/precomp.h>

class UIWidgetCache;
class UIRegistry;
class UIWidget;
struct UINode;

class UIBuilder {

public:
    explicit UIBuilder(const UIRegistry& InRegistry) : Registry(InRegistry) {}

    // Add Build option if needed ? 
    std::unique_ptr<UIWidget> Build(const UINode& node, std::unique_ptr<UIWidget> PreviousRoot, UIWidgetCache* PrevCache,UIWidgetCache* NextCache);

    void HotReload();
private:
    std::unique_ptr<UIWidget> Build_Internal(const UINode& node,std::unique_ptr<UIWidget>& PreviousRoot,UIWidgetCache* PrevCache, UIWidgetCache* NextCache);

    void BuildChildren(UIWidget& Widget,const UINode& Node, std::unique_ptr<UIWidget>& PreviousRoot, UIWidgetCache* PrevCache, UIWidgetCache* NextCache);
    std::unique_ptr<UIWidget> ExtractFromCache(std::unique_ptr<UIWidget>& InRoot,const std::string& InId);
    
    const UIRegistry& Registry;
};