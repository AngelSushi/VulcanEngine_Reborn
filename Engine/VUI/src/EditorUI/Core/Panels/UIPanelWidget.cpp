#include <EditorUI/Core/Panels/UIPanelWidget.h>

void UIPanelWidget::AddChild(std::unique_ptr<UIWidget> InChild) {
    InChild->SetParent(this);

    std::unique_ptr<UISlot> Slot = GetSlotClass();
    InChild->SetSlot(std::move(Slot));
    
    Children.push_back(std::move(InChild));
}

// This function must be implemented by the derived class to return the appropriate UISlot type for the container.
std::unique_ptr<UISlot> UIPanelWidget::GetSlotClass() {
    Expects(0);
}

bool UIPanelWidget::CanHaveMultipleChildren() const {
    return true;
}

bool UIPanelWidget::CanAddMoreChildren() const {
    return CanHaveMultipleChildren() || Children.empty();
}


const std::vector<std::unique_ptr<UIWidget>>& UIPanelWidget::GetChildren() const {
    return Children;
}

int UIPanelWidget::GetChildrenCount() const {
    return static_cast<int>(Children.size());
}

void UIPanelWidget::Render(UIRenderContext& InContext) {
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
