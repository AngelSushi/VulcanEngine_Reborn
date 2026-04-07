#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UINode.h>
#include <EditorUI/Runtime/UIRenderContext.h>

#include "Vector2.h"
#include "Types/VColor.h"

class UIWidget {
    
public:
    virtual ~UIWidget() = default; 

    void Link(const UINode& InNode);
    void AddChild(std::unique_ptr<UIWidget> InChild);
    
     virtual void ApplyProps();
     virtual void Render(UIRenderContext& InContext) const;
     virtual Clay_LayoutConfig BuildLayout() const;
     virtual Clay_ElementDeclaration Build() const;

    const std::string& GetID() const { return Id; }
    const std::string& GetType() const { return Type; }
    const std::vector<std::unique_ptr<UIWidget>>& GetChildren();

    const VMath::Vector2f& GetPosition() const;
    const VMath::Vector2f& GetSize() const;

private:
    Clay_String GetClayString() const;

    UINode* Node = nullptr;
    std::string Id;
    std::string Type;
    
    std::vector<std::unique_ptr<UIWidget>> Children;

    VulcanEngine::VColor BackgroundColor;
    VMath::Vector2f Position;
    ClaySize Size;
};
