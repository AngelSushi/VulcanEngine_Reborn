#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UINode.h>
#include <EditorUI/Runtime/UIRenderContext.h>

#include "EventTrigger.h"
#include "Rect.h"
#include "Vector2.h"
#include "EditorUI/EWidgetVisibility.h"
#include "Types/VColor.h"

class UIWidget {
    friend class WidgetApplication;

    using WidgetEventType = std::function<void()>;
public:
    UIWidget() = default;
    virtual ~UIWidget() = default;

    void Link(const UINode& InNode);
    void AddChild(std::unique_ptr<UIWidget> InChild);

    virtual void ApplyProps();
    virtual void Layout();
    virtual void Initialized(WidgetApplication& WidgetApplication);
    
    virtual void Render(UIRenderContext& InContext) const;
    virtual Clay_LayoutConfig BuildLayout() const;
    virtual Clay_ElementDeclaration Build() const;

    bool HasParent() const;
    UIWidget* GetParent() const;
    void SetParent(UIWidget* InParent);

    EWidgetVisibility GetVisibility() const;
    VMath::Rect GetBounds() const;

    const std::string& GetID() const { return Id; }
    const std::string& GetType() const { return Type; }
    const std::vector<std::unique_ptr<UIWidget>>& GetChildren() const;
    const int GetChildrenCount() const;

    const VMath::Vector2f& GetPosition() const;
    VMath::Vector2f GetSize() const;

    // Maybe change the SetPoition for future, UIWidget should represent a node in the UI tree, and its position should be determined by its parent and layout, not set directly.
    void SetPosition(const VMath::Vector2f& InPosition);

protected:
    virtual bool SupportFocus();
    virtual bool NativeOnFocusReceived();
    virtual void NativeOnFocusLost();

    bool bIsFocusable = false;
    UINode* Node = nullptr;
    EWidgetVisibility Visibility = EWidgetVisibility::Visible;

private:
    Clay_String GetClayString() const;
    float ResolveAxisSize(ClayAxisSize Axis,float MaxValue) const;

    void DispatchEvent(const std::string& EventName);

    std::string Id;
    std::string Type;
    int WindowIndex;

    std::vector<std::unique_ptr<UIWidget>> Children;
    UIWidget* Parent = nullptr;

    VulcanEngine::VColor BackgroundColor;
    VulcanEngine::VColor OriginColor;
    VulcanEngine::VColor HoverColor;
    VulcanEngine::VColor ClickedColor;

    VMath::Vector2f Position;
    ClaySize Size;

public:
    VulcanEngine::EventTrigger<WidgetEventType> OnFocus;
    VulcanEngine::EventTrigger<WidgetEventType> OnFocusLost;
    VulcanEngine::EventTrigger<WidgetEventType> OnHover;
    VulcanEngine::EventTrigger<WidgetEventType> OnClicked;
    
};
