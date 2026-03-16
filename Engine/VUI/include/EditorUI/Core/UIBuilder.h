#pragma once
#include <CoreAPI/precomp.h>

#include "UIRegistry.h"
#include "UIWidgetCache.h"
#include <EditorUI/Core/UIWidget.h>

struct UINode;

class UIBuilder {

public:
    UIBuilder(UIRegistry& InRegistry);
    UIBuilder& operator=(const UIBuilder& Builder);

    std::unique_ptr<UIWidget> Build(const UINode& Root,UIWidgetCache* PrevCache,UIWidgetCache* NextCache);
private:
    std::unique_ptr<UIWidget> Build_Internal(const UINode& Root,UIWidgetCache* PrevCache,UIWidgetCache* NextCache);

    UIRegistry& Registry;
};