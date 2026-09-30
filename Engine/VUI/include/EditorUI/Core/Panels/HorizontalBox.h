#pragma once
#include "UIPanelWidget.h"


class HorizontalBox : public UIPanelWidget {

public:
    
    std::unique_ptr<UISlot> GetSlotClass() override;
    Clay_ElementDeclaration Build() override;
    
    // Maybe this should be generic in UIContainer, but for better understanding we let this function here for now
    void Render(UIRenderContext& InContext) override;
};