#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Core/UINode.h>
#include <EditorUI/Runtime/UIRenderContext.h>

class UIWidget {
    
public:
    virtual ~UIWidget() = default; 

    void Link(const UINode& InNode);
    
     void ApplyProps() const;
     void Render(UIRenderContext& InContext) const;

    const std::string& GetID() { return Id; }
    const std::string& GetType() { return Type; }
    const std::vector<std::unique_ptr<UIWidget>>& GetChildren();

private:
    const UINode* Node = nullptr;
    std::string Id;
    std::string Type;

    std::vector<std::unique_ptr<UIWidget>> Children;

};
