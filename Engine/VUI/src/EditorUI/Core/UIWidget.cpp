#include <EditorUI/Core/UIWidget.h>

void UIWidget::Link(const UINode& InNode) {
    Node = &InNode;
    Id = InNode.Id;
    Type = InNode.Type;
}

void UIWidget::ApplyProps() const {
    Expects(0);
}

void UIWidget::Render(UIRenderContext& InContext) const
{
}

const std::vector<std::unique_ptr<UIWidget>>& UIWidget::GetChildren() {
    return Children;
}
