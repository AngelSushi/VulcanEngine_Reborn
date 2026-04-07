#include <iostream>
#include <EditorUI/Core/UIWidget.h>

void UIWidget::Link(const UINode& InNode) {
    Node = const_cast<UINode*>(&InNode);
    Id = InNode.Id;
    Type = InNode.Type;
}

void UIWidget::AddChild(std::unique_ptr<UIWidget> InChild) {
    Children.push_back(std::move(InChild));
}

void UIWidget::ApplyProps() {
    // Care of Get returning nothing or not std::string ?
    // Care of TryProp or TryProp().Get making app crash when the property is not exist
    BackgroundColor = VulcanEngine::VColor(Node->TryProp("backgroundColor").Get<std::string>());
    Position = Node->TryProp("position").Get<VMath::Vector2f>();
    Size = Node->TryProp("size").Get<ClaySize>();
}

Clay_LayoutConfig UIWidget::BuildLayout() const {
    Clay_LayoutConfig Config = {};
    Config.sizing = Size.ToClaySize();
    return Config;
}

Clay_ElementDeclaration UIWidget::Build() const {
    Clay_ElementDeclaration Declaration = {};
    Declaration.layout = BuildLayout();
    Declaration.floating.attachTo = CLAY_ATTACH_TO_PARENT;
    Declaration.floating.offset = { Position.x, Position.y };

    Declaration.backgroundColor = {
        BackgroundColor.R() * 255.f,
        BackgroundColor.G() * 255.f,
        BackgroundColor.B() * 255.f,
        BackgroundColor.A() * 255.f
    };
    
    return Declaration;
}

Clay_String UIWidget::GetClayString() const {
    Clay_String CString = {};
    CString.length = (int)Type.size();
    CString.chars = Type.c_str();
    return CString;
}

void UIWidget::Render(UIRenderContext& InContext) const {
    const Clay_ElementDeclaration Declaration = Build();
 
    CLAY(Clay_GetElementId(GetClayString()), Declaration) {
        for (const auto& Child : Children) {
            Child->Render(InContext);
        }

        
    }
}

const std::vector<std::unique_ptr<UIWidget>>& UIWidget::GetChildren() {
    return Children;
}

const VMath::Vector2f& UIWidget::GetPosition() const {
    return Position;
}

const VMath::Vector2f& UIWidget::GetSize() const {
    VMath::Vector2f AbsSize;

    AbsSize.x = Size.X.Value;
    AbsSize.y = Size.Y.Value;

    return AbsSize;
}
