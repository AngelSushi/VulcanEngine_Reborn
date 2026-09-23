#include <iostream>
#include <EditorUI/Core/UIWidget.h>
#include <CoreAPI/VWindow.h>
#include <CoreAPI/VCore.h>

#include "EditorUI/Runtime/WidgetApplication.h"

void UIWidget::Link(const UINode& InNode) {
    Node = InNode;
    Id = InNode.Id;
    Type = InNode.Type;
    WindowIndex = InNode.WindowIndex;
}

void UIWidget::ApplyProps() {
    BackgroundColor = VColor(Node.TryPropValue("backgroundColor").Get<std::string>());
    OriginColor = BackgroundColor;

    auto [HoverColorValue, bSucceedHover] = Node.TryProp("hoverColor");
    HoverColor = bSucceedHover ? VColor(HoverColorValue.Get<std::string>()) : BackgroundColor.Lighten(0.3f);

    auto [ClickedColorValue,bSucceedClicked] = Node.TryProp("clickedColor");
    ClickedColor = bSucceedClicked ? VColor(ClickedColorValue.Get<std::string>()) : HoverColor.Darken(0.3f);
    
    bIsFocusable = Node.TryPropValue("focusable").Get<bool>();
}


void UIWidget::Initialized(WidgetApplication& WidgetApplication) {
    // Is it usefull ? We alreaedy pass GetCurrentWiindowGeometry insiide the Build() function, so we can remove this line if we want to save some performance  
    //    InternalGeometry = WidgetApplication.GetCurrentWindowGeometry();
}

void UIWidget::ResolveLayout() {
    Clay_ElementData ElementData = Clay_GetElementData(Clay_GetElementId(GetClayString()));

    if (ElementData.found) {
        VMath::Vector2f Size = { ElementData.boundingBox.width, ElementData.boundingBox.height };
        VMath::Vector2f Center = { ElementData.boundingBox.x + ElementData.boundingBox.width / 2, ElementData.boundingBox.y + ElementData.boundingBox.height / 2 };

        InternalGeometry = VMath::Rect(Center, Size);
    }
}

Clay_ElementDeclaration UIWidget::Build() {
    Clay_ElementDeclaration Declaration = {};
    Declaration.layout = {};

    ResolveLayout();
    
    // Get window geometry if no parent, else get parent geometry
  
    if ((Slot && Slot->UseFloatingLayout()) || (!Slot)) {
        VMath::Rect ParentGeometry = HasParent() ? GetParent()->GetGeometry() : WidgetApplication::Get().GetCurrentWindowGeometry();
        VMath::Rect Geometry = Slot ? Slot->ComputeGeometry(ParentGeometry) : ParentGeometry;

        Declaration.floating.parentId = HasParent() ? Clay_GetElementId(GetClayString()).id : Clay_GetElementId(Clay_String()).id;
        Declaration.floating.attachTo = HasParent() ? CLAY_ATTACH_TO_PARENT : CLAY_ATTACH_TO_ROOT;
        Declaration.floating.offset = { Geometry.Min.x, Geometry.Min.y };

        Declaration.layout.sizing = {
            CLAY_SIZING_FIXED(Geometry.Size.x),
            CLAY_SIZING_FIXED(Geometry.Size.y)
        };
    }
    else if (Slot) {
        Declaration.layout.sizing = Slot->ComputeSizing();
    }

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

Clay_String UIWidget::GetClayString() const {
    Clay_String CString = {};
    CString.length = (int)Id.size();
    CString.chars = Id.c_str();
    return CString;
}

void UIWidget::Render(UIRenderContext& InContext) {
    const Clay_ElementDeclaration Declaration = Build();

    if (Visibility == EWidgetVisibility::Collasped || Visibility == EWidgetVisibility::Hidden) {
        return;
    }
    
    CLAY(Clay_GetElementId(GetClayString()), Declaration) {
    }
}

void UIWidget::SetSlot(std::unique_ptr<UISlot> InSlot) {
    Slot = std::move(InSlot);
    Slot->ApplyProps(Node);
}

UISlot* UIWidget::GetSlot() const {
    return Slot.get();
}

VMath::Rect UIWidget::GetGeometry() const {
    return InternalGeometry;
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

void UIWidget::DispatchEvent(const std::string& EventName) {
    if (EventName == "OnFocus") {
        OnFocus.Trigger();
    }
}
