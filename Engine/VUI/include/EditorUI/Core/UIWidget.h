#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UINode.h>
#include <EditorUI/Runtime/UIRenderContext.h>

#include "EventTrigger.h"
#include "EditorUI/EWidgetVisibility.h"
#include "Slot/UISlot.h"
#include "Types/VColor.h"

class UIPanelWidget;

class VUI_API UIWidget {
    friend class WidgetApplication;

    using WidgetEventType = std::function<void()>;
public:
    UIWidget() = default;
    virtual ~UIWidget() = default;

    void Link(const UINode& InNode);

    // void AddChild(std::unique_ptr<UIWidget> InChild);

    virtual void ApplyProps();
    virtual void Initialized(WidgetApplication& WidgetApplication);
    
    virtual void Render(UIRenderContext& InContext);

    virtual Clay_ElementDeclaration Build();
    void ResolveLayout();

    bool HasParent() const;
    UIPanelWidget* GetParent() const;
    void SetParent(UIPanelWidget* InParent);

    EWidgetVisibility GetVisibility() const;

    const std::string& GetID() const { return Id; }
    const std::string& GetType() const { return Type; }


    void SetSlot(std::unique_ptr<UISlot> InSlot);
    UISlot* GetSlot() const;


    VMath::Rect GetGeometry() const;
    
protected:
    virtual bool SupportFocus();
    virtual bool NativeOnFocusReceived();
    virtual void NativeOnFocusLost();

    bool bIsFocusable = false;
    UINode Node;
    EWidgetVisibility Visibility = EWidgetVisibility::Visible;
    Clay_String GetClayString() const;

protected:
    void DispatchEvent(const std::string& EventName);
    
    std::string Id;
    std::string Type;
    int WindowIndex;

    /*
     *@brief The geometry of the widget, which is computed based on its position, size, and parent geometry. This is used for rendering and hit testing. The geometry is compute one frame after the widget is created, so it may not be valid immediately after creation. It is updated every frame during the ResolveLayout() call.
     */
    VMath::Rect InternalGeometry;

    UIPanelWidget* Parent = nullptr;

    VColor BackgroundColor;
    VColor OriginColor;
    VColor HoverColor;
    VColor ClickedColor;

    std::unique_ptr<UISlot> Slot;

public:
    EventTrigger<WidgetEventType> OnFocus;
    EventTrigger<WidgetEventType> OnFocusLost;
    EventTrigger<WidgetEventType> OnHover;
    EventTrigger<WidgetEventType> OnClicked;
    
};
