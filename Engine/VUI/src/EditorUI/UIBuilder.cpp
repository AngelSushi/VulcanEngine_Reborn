#include <EditorUI/UIBuilder.h>

std::unique_ptr<UIWidget> UIBuilder::Build(const UINode& Root, std::unique_ptr<UIWidget> PrevRoot, UIWidgetCache* PrevCache,UIWidgetCache* NextCache) {
    if (!NextCache)
        NextCache->Clear();
    
    return Build_Internal(Root, PrevRoot, PrevCache, NextCache);
}

std::unique_ptr<UIWidget> UIBuilder::Build_Internal(const UINode& Root, std::unique_ptr<UIWidget>& PrevRoot, UIWidgetCache* PrevCache,UIWidgetCache* NextCache)
{
    // Maybe not worth cause we recreate UIRegisteredType every time, but we can optimize it later if needed.
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

    ApplyDefaultSchemas();

    
}
    
