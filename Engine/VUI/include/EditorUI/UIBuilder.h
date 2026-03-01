#pragma once
#include <CoreAPI/precomp.h>

#include "UIRegistry.h"
#include "UIWidget.h"
#include "UIWidgetCache.h"

struct UINode;

class UIBuilder {

public:
    UIBuilder(const UIRegistry& InRegistry) : Registry(InRegistry) {}
    

    std::unique_ptr<UIWidget> Build(const UINode& Root,std::unique_ptr<UIWidget> PrevRoot,UIWidgetCache* PrevCache,UIWidgetCache* NextCache);
private:
    std::unique_ptr<UIWidget> Build_Internal(const UINode& Root,std::unique_ptr<UIWidget>& PrevRoot,UIWidgetCache* PrevCache,UIWidgetCache* NextCache);

    const UIRegistry& Registry;
};