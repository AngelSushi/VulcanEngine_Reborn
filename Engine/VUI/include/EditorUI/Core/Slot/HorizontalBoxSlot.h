#pragma once
#include <CoreAPI/precomp.h>
#include "UISlot.h"
#include "EditorUI/Core/Alignment.h"
#include "EditorUI/Core/UINode.h"

class VUI_API HorizontalBoxSlot : public UISlot {

public:
    void ApplyProps(UINode& Node) override;
    bool UseFloatingLayout() const override;
    Clay_Sizing ComputeSizing() const override;

private:
    EHorizontalAlignment HorizontalAlignment = EHorizontalAlignment::Left;
    EVerticalAlignment VerticalAlignment = EVerticalAlignment::Top; 
};
