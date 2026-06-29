#include <iostream>
#include <EditorUI/Core/UIWidget.h>
#include <CoreAPI/VWindow.h>
#include <CoreAPI/VCore.h>

void UIWidget::Link(const UINode& InNode) {
    Node = const_cast<UINode*>(&InNode);
    Id = InNode.Id;
    Type = InNode.Type;
    WindowIndex = InNode.WindowIndex;
}

void UIWidget::AddChild(std::unique_ptr<UIWidget> InChild) {
    InChild->SetParent(this);
    Children.push_back(std::move(InChild));
}

void UIWidget::ApplyProps() {
    BackgroundColor = VulcanEngine::VColor(Node->TryPropValue("backgroundColor").Get<std::string>());
    OriginColor = BackgroundColor;

    auto [HoverColorValue, bSucceedHover] = Node->TryProp("hoverColor");
    HoverColor = bSucceedHover ? VulcanEngine::VColor(HoverColorValue.Get<std::string>()) : BackgroundColor.Lighten(0.3f);

    auto [ClickedColorValue,bSucceedClicked] = Node->TryProp("clickedColor");
    ClickedColor = bSucceedClicked ? VulcanEngine::VColor(ClickedColorValue.Get<std::string>()) : HoverColor.Darken(0.3f);

    Position = Node->TryPropValue("position").Get<VMath::Vector2f>();
    Size = Node->TryPropValue("size").Get<ClaySize>();

    bIsFocusable = Node->TryPropValue("focusable").Get<bool>();
}

void UIWidget::Layout() {
}

void UIWidget::Initialized(WidgetApplication& WidgetApplication) {
}

Clay_LayoutConfig UIWidget::BuildLayout() const {
    Clay_LayoutConfig Config = {};
    
    VMath::Vector2f ComputedSize = GetSize();
    Config.sizing.width = CLAY_SIZING_FIXED(ComputedSize.x);
    Config.sizing.height = CLAY_SIZING_FIXED(ComputedSize.y);
    
    return Config;
}

Clay_ElementDeclaration UIWidget::Build() const {
    Clay_ElementDeclaration Declaration = {};
    Declaration.layout = BuildLayout();
    Declaration.floating.parentId = HasParent() ? Clay_GetElementId(GetClayString()).id : Clay_GetElementId(Clay_String()).id;
    Declaration.floating.attachTo = HasParent() ? CLAY_ATTACH_TO_PARENT : CLAY_ATTACH_TO_ROOT;
    Declaration.floating.offset = { Position.x, Position.y };

    Declaration.backgroundColor = {
        BackgroundColor.R() * 255.f,
        BackgroundColor.G() * 255.f,
        BackgroundColor.B() * 255.f,
        BackgroundColor.A() * 255.f
    };

    return Declaration;
}

bool UIWidget::HasParent() const {
    return Parent != nullptr;
}

UIWidget* UIWidget::GetParent() const {
    return Parent;
}

void UIWidget::SetParent(UIWidget* InParent) {
    Parent = InParent;
}

EWidgetVisibility UIWidget::GetVisibility() const {
    return Visibility;
}

VMath::Rect UIWidget::GetBounds() const {
    VMath::Vector2i Center = Position + GetSize() / 2;
    return VMath::Rect(Center, GetSize());
}

Clay_String UIWidget::GetClayString() const {
    Clay_String CString = {};
    CString.length = (int)Id.size();
    CString.chars = Id.c_str();
    return CString;
}

void UIWidget::Render(UIRenderContext& InContext) const {
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

const std::vector<std::unique_ptr<UIWidget>>& UIWidget::GetChildren() const {
    return Children;
}

const int UIWidget::GetChildrenCount() const {
    return static_cast<int>(Children.size());
}

const VMath::Vector2f& UIWidget::GetPosition() const {
    return Position;
}

VMath::Vector2f UIWidget::GetSize() const {
    VulcanEngine::VWindow& Window = VulcanCore::VCore::GetInstance().GetWindowByIndex(WindowIndex);

    VMath::Vector2f WidgetSize = HasParent() ?
        VMath::Vector2f(ResolveAxisSize(Size.X,Parent->GetSize().x),ResolveAxisSize(Size.Y,Parent->GetSize().y))
    : VMath::Vector2f(ResolveAxisSize(Size.X,Window.GetSize().first),ResolveAxisSize(Size.Y,Window.GetSize().second));
    
    return WidgetSize;
}

void UIWidget::SetPosition(const VMath::Vector2f& InPosition) {
    Position = InPosition;
}

bool UIWidget::SupportFocus() {
    return bIsFocusable;
}

bool UIWidget::NativeOnFocusReceived() {
    BackgroundColor = HoverColor;

    DispatchEvent("OnFocus");
    return true;
}

void UIWidget::NativeOnFocusLost() {
    BackgroundColor = OriginColor;
}

float UIWidget::ResolveAxisSize(ClayAxisSize Axis,float MaxValue) const {
    switch (Axis.Type) {
        case EClaySizeType::GROW:
            return MaxValue;
        default:
            return Axis.Value;
    }
}

void UIWidget::DispatchEvent(const std::string& EventName) {
    if (EventName == "OnFocus") {
        OnFocus.Trigger();
    }
}
