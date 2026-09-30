#pragma once
#include <CoreAPI/precomp.h>
#include "UISlot.h"
#include "EditorUI/Core/Alignment.h"
#include "EditorUI/Core/UINode.h"


/*
 * @brief A slot for a widget inside a Button. It defines how the widget should be aligned and sized within the Button.
 * This should be a more generic class (not only for Button), if there is a need for a more generic class, we can rename it to something like "BoxSlot" or "ContainerSlot"
 */

class VUI_API ButtonSlot : public UISlot {

public:
    void ApplyProps(UINode& Node) override;
    bool UseFloatingLayout() const override;
    Clay_Sizing ComputeSizing() const override;
    Clay_TextAlignment ComputeAlignment() const override;
    Clay_ChildAlignment ComputeChildAlignment() const override;

    Padding GetSlotPadding() const;

private:
    EHorizontalAlignment HorizontalAlignment = EHorizontalAlignment::Left;
    EVerticalAlignment VerticalAlignment = EVerticalAlignment::Top;

    Padding SlotPadding;
};
