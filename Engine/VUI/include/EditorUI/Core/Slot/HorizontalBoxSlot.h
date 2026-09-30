#pragma once
#include <CoreAPI/precomp.h>
#include "UISlot.h"
#include "EditorUI/Core/Alignment.h"
#include "EditorUI/Core/UINode.h"


/*
 * @brief A slot for a widget inside a HorizontalBox. It defines how the widget should be aligned and sized within the HorizontalBox.
 * It should have a fill or auto mode
 * The diff between HorizontalBoxSlot and ButtonBoxSlot is the full or auto mode
 */

class VUI_API HorizontalBoxSlot : public UISlot {

public:
    void ApplyProps(UINode& Node) override;
    bool UseFloatingLayout() const override;
    Clay_Sizing ComputeSizing() const override;
    Clay_ChildAlignment ComputeChildAlignment() const override;

private:
    EHorizontalAlignment HorizontalAlignment = EHorizontalAlignment::Left;
    EVerticalAlignment VerticalAlignment = EVerticalAlignment::Top; 
};
