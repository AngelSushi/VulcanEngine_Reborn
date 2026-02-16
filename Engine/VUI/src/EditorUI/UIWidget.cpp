#include <EditorUI/UIWidget.h>

void UIWidget::BuildNode(const UINode& InNode) {
    Node = &InNode;
    Id = InNode.Id;
    Type = InNode.Type;
}

void UIWidget::ApplyProps() const {
    Expects(0);
}
