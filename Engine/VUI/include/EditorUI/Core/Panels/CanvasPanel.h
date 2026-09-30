#pragma once

#include <CoreAPI/precomp.h>
#include "UIPanelWidget.h"


class VUI_API CanvasPanel : public UIPanelWidget {

public:
    
    std::unique_ptr<UISlot> GetSlotClass() override;
    
    // Maybe this should be generic in UIContainer, but for better understanding we let this function here for now
    void Render(UIRenderContext& InContext) override;
};