#include <EditorUI/Core/UIBuilder.h>

UIBuilder::UIBuilder(UIRegistry& InRegistry) : Registry(InRegistry) {
}

UIBuilder& UIBuilder::operator=(const UIBuilder& Builder) {
    Registry = Builder.Registry;
    return *this;
}


std::unique_ptr<UIWidget> UIBuilder::Build(const UINode& Root, UIWidgetCache* PrevCache,UIWidgetCache* NextCache) {
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
        Widget  = PrevCache->Take(Root.Id);

        // If we have a widget with the same ID in memory but the type is different, we need to discard it and create a new one.
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

    // Build Childrens
    for (const UINode& Child : Local.Children) {
        std::unique_ptr<UIWidget> ChildWidget = Build_Internal(Child, PrevCache, NextCache);
        if (ChildWidget) {
            Widget->AddChild(std::move(ChildWidget));
        }
    }


    
    if (NextCache) { // ???????????? what are we doing here
        NextCache->Put(std::move(Widget));
        return NextCache->Take(Local.Id);
        
    }

    return Widget;
    
}
    
