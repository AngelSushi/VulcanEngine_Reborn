#pragma once
#include <CoreAPI/precomp.h>
#include "UISlot.h"
#include "Vector2.h"
#include "EditorUI/Core/Padding.h"
#include "EditorUI/Core/UINode.h"

class VUI_API CanvasSlot : public UISlot {

public:
    void ApplyProps(UINode& Node) override;
    bool UseFloatingLayout() const override;
    
    VMath::Rect ComputeGeometry(const VMath::Rect& ParentGeometry) const override;
    
private:
    VMath::Vector2f AnchorMin;
    VMath::Vector2f AnchorMax;
    Padding Padding_;

    VMath::Vector2f Size;
    
    /*
     * @brief The local anchor of the widget to properly place it.
     */
    VMath::Vector2f Alignment;
};
