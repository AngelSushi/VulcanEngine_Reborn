#include <EditorUI/Core/Panels/UIContentWidget.h>

bool UIContentWidget::CanHaveMultipleChildren() const {
    return false;
}

UIWidget* UIContentWidget::GetContent() const {
    return Children.empty() ? nullptr : Children[0].get();
}
