#pragma once
#include <Rect.h>
#include <EditorUI/Core/UINode.h>

class UISlot {

public:
    virtual ~UISlot() = default;

    virtual void ApplyProps(UINode& Node) = 0;
    virtual bool UseFloatingLayout() const = 0;

    /*
     * @brief Computes the geometry of the widget based on the parent geometry and the slot properties.
     */
    virtual VMath::Rect ComputeGeometry(const VMath::Rect& ParentGeometry) const;


    /*
     * @brief Computes the sizing of the widget based on the slot properties.
     */
    virtual Clay_Sizing ComputeSizing() const;
};
