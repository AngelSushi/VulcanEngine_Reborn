#include <EditorUI/Core/Panels/HorizontalBox.h>

#include "EditorUI/Core/Slot/CanvasSlot.h"
#include "EditorUI/Core/Slot/HorizontalBoxSlot.h"

std::unique_ptr<UISlot> HorizontalBox::GetSlotClass() {
    return std::make_unique<HorizontalBoxSlot>();
}

Clay_ElementDeclaration HorizontalBox::Build() {
    Clay_ElementDeclaration Declaration = UIPanelWidget::Build();
    Declaration.layout.layoutDirection = CLAY_LEFT_TO_RIGHT;
    
    return Declaration;
}

void HorizontalBox::Render(UIRenderContext& InContext) {
    UIPanelWidget::Render(InContext);
}


