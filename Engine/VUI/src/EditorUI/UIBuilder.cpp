#include <Windows.h>
#include <EditorUI/UIBuilder.h>

#include "EditorUI/UIRegistry.h"
#include "EditorUI/UIWidgetCache.h"

// Called when we want to build the UI from a UINode structure.
std::unique_ptr<UIWidget> UIBuilder::Build(const UINode& Node, std::unique_ptr<UIWidget> PreviousRoot,UIWidgetCache* PrevCache, UIWidgetCache* NextCache) {
    if (NextCache) {
        NextCache->Clear();
    }

    return Build_Internal(Node,PreviousRoot,PrevCache,NextCache);
}

// Called when we want to rebuild the UI from the app directly. 
void UIBuilder::HotReload() {
    Expects(0);
}

std::unique_ptr<UIWidget> UIBuilder::Build_Internal(const UINode& Node, std::unique_ptr<UIWidget>& PreviousRoot,UIWidgetCache* PrevCache, UIWidgetCache* NextCache) {
    const UIRegistryType* Type = Registry.Find(Node.Type);

    if (!Type) {
        return nullptr;
    }

    std::unique_ptr<UIWidget> Widget;

    if (PrevCache->Has(Node.Id)) {
        Widget = ExtractFromCache(PreviousRoot,Node.Id);

        if (Widget && Widget->GetType() != Node.Type) {
            Widget.reset();
        }
    }

    if (!Widget) {
        Widget = Type->Factory();
    }

    Expects(Widget != nullptr);

    // Apply Schemas ? 

    if (NextCache) {
        NextCache->Put(Widget.get());
    }

    BuildChildren(*Widget,Node,PreviousRoot,PrevCache,NextCache);

    return Widget;
}

void UIBuilder::BuildChildren(UIWidget& Widget, const UINode& Node, std::unique_ptr<UIWidget>& PreviousRoot,UIWidgetCache* PrevCache, UIWidgetCache* NextCache) {
    Widget.Children.clear();
    Widget.Children.reserve(Node.Children.size());

    for (size_t i = 0; i < Node.Children.size(); i++) {
        const UINode& Child = Node.Children[i];
        auto ChildWidget = Build_Internal(Child,PreviousRoot,PrevCache,NextCache);
        Expects(ChildWidget != nullptr);
        Widget.Children.push_back(std::move(ChildWidget));
    }
    
}

std::unique_ptr<UIWidget> UIBuilder::ExtractFromCache(std::unique_ptr<UIWidget>& InRoot, const std::string& InId) {
    if (!InRoot){
        return nullptr;
    }

    if (InRoot->GetID() == InId) {
        return std::move(InRoot);
    }

    // A VERIFIER SI CELA NE POSE PAS DE PROBLEMES ?
    // On fait une copie du widget qu'on move après ? 
    for (auto Widget : InRoot->GetChildren()) {
        if (!Widget) {
            continue;
        }

        if (Widget->GetID() == InId) {
            auto out = std::move(Widget);
            return out;
        }

        if (auto FoundedWidget = ExtractFromCache(Widget,InId)) {
            return FoundedWidget;
        }
    }

    return nullptr;
}

