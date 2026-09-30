#include <EditorUI/Core/Panels/CanvasPanel.h>
#include "EditorUI/Core/Slot/CanvasSlot.h"

std::unique_ptr<UISlot> CanvasPanel::GetSlotClass() {
    return std::make_unique<CanvasSlot>();
}

void CanvasPanel::Render(UIRenderContext& InContext) {
    const Clay_ElementDeclaration Declaration = Build();

    if (Visibility == EWidgetVisibility::Collasped || Visibility == EWidgetVisibility::Hidden) {
        return;
    }

    CLAY(Clay_GetElementId(GetClayString()), Declaration) {
        for (const auto& Child : Children) {
            Child->Render(InContext);
        }
    }
    
}
