#pragma once
#include <CoreAPI/precomp.h>
#include "EditorUI/Core/UIWidget.h"
#include "EditorUI/Core/Slot/UISlot.h"


class VUI_API UIPanelWidget : public UIWidget {

public:
    void AddChild(std::unique_ptr<UIWidget> InChild);
    virtual std::unique_ptr<UISlot> GetSlotClass();

    virtual bool CanHaveMultipleChildren() const;
    bool CanAddMoreChildren() const;
    

    const std::vector<std::unique_ptr<UIWidget>>& GetChildren() const;
    int GetChildrenCount() const;

    void Render(UIRenderContext& InContext) override;

protected:
    std::vector<std::unique_ptr<UIWidget>> Children;
};
