#include <EditorUI/Core/UIBuilder.h>

#include "EditorUI/Core/Panels/UIPanelWidget.h"
#include "EditorUI/Runtime/WidgetApplication.h"

UIBuilder::UIBuilder(UIRegistry& InRegistry) : Registry(InRegistry) {
}

UIBuilder& UIBuilder::operator=(const UIBuilder& Builder) {
    Registry = Builder.Registry;
    return *this;
}

std::unique_ptr<UIWidget> UIBuilder::Build(const UINode& Root, UIWidgetCache* PrevCache,UIWidgetCache* NextCache) {
    // Cache-system doesn't work as intended. The condition appear to be always true 
    if (NextCache)
        NextCache->Clear();

    return Build_Internal(Root, PrevCache, NextCache);
}

std::unique_ptr<UIWidget> UIBuilder::Build_Internal(const UINode& Root, UIWidgetCache* PrevCache,UIWidgetCache* NextCache) {
    UIRegisteredType RegisteredType = Registry.Find(Root.Type);

    if (RegisteredType.IsNull())
        return nullptr;

    std::unique_ptr<UIWidget> Widget;

    if (PrevCache->Has(Root.Id)) {
        Widget = PrevCache->Take(Root.Id);

        if (Widget->GetType() != Root.Type) {
            Widget.reset();
        }
    }

    if (!Widget) Widget = RegisteredType.Create();
    if (!Widget) return nullptr;

    UINode Local = Root;
    ApplyDefaultSchemas(Local.Properties,RegisteredType.Schemas);

    Widget->Link(Local);
    Widget->ApplyProps();

    // Changee for future cast system
    if (UIPanelWidget* Panel = dynamic_cast<UIPanelWidget*>(Widget.get())) {

        if (!Panel->CanHaveMultipleChildren() && Local.Children.size() > 1) {
            // Log error, we can't add more than one child to this panel

            // is goto a good practice ? 
            goto Assignation;
        }
        
        for (const UINode& ChildNode : Local.Children) {
            if (!Panel->CanAddMoreChildren()) {
                break;
            }
            
            std::unique_ptr<UIWidget> ChildWidget = Build_Internal(ChildNode, PrevCache, NextCache);
            if (ChildWidget) {
                Panel->AddChild(std::move(ChildWidget));
            }
        }
    }


    Assignation:
    if (NextCache) {
        NextCache->Put(std::move(Widget));
        return NextCache->Take(Local.Id);
    }

    return Widget;
}
