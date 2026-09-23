#include <EditorUI/Core/Slot/CanvasSlot.h>

void CanvasSlot::ApplyProps(UINode& Node) {
    Padding_ = Node.TryPropValue("padding").Get<Padding>();
    Size = Node.TryPropValue("size").Get<Vector2f>();
    AnchorMin = Node.TryPropValue("anchorMin").Get<VMath::Vector2f>();
    AnchorMax = Node.TryPropValue("anchorMax").Get<VMath::Vector2f>();
}

bool CanvasSlot::UseFloatingLayout() const {
    return true;
}

VMath::Rect CanvasSlot::ComputeGeometry(const VMath::Rect& ParentGeometry) const {
    VMath::Vector2f MinPoint = {
        ParentGeometry.Min.x + ParentGeometry.Size.x * AnchorMin.x,
        ParentGeometry.Min.y + ParentGeometry.Size.y * AnchorMin.y
    };

    VMath::Vector2f MaxPoint = {
        ParentGeometry.Min.x + ParentGeometry.Size.x * AnchorMax.x,
        ParentGeometry.Min.y + ParentGeometry.Size.y * AnchorMax.y  
    };

    bool bStretchX = AnchorMin.x != AnchorMax.x;
    bool bStretchY = AnchorMin.y != AnchorMax.y;

    Vector2f FinalSize = {
        bStretchX ? MaxPoint.x - MinPoint.x - Padding_.Left - Padding_.Right : Size.x,
        bStretchY ? MaxPoint.y - MinPoint.y - Padding_.Top - Padding_.Bottom : Size.y
    };
    
    VMath::Vector2f TopLeft = {
        bStretchX ? MinPoint.x + Padding_.Left : MinPoint.x + Padding_.Left - Size.x * Alignment.x,
        bStretchY ? MinPoint.y + Padding_.Top : MinPoint.y + Padding_.Top - Size.y * Alignment.y
    };

    return VMath::Rect(TopLeft + FinalSize / 2, FinalSize);
}
