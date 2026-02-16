#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/UINode.h>

class UIRenderContext;

class UIWidget {
    friend class UIBuilder;
    
public:
    virtual ~UIWidget() = default; 

    void BuildNode(const UINode& InNode);
    
    virtual void ApplyProps() const;
    virtual void Render(UIRenderContext& InContext) const = 0;

    const std::string& GetID() { return Id; }
    const std::string& GetType() { return Type; }
    const std::vector<std::unique_ptr<UIWidget>>& GetChildren() { return Children; }

private:
    const UINode* Node = nullptr;
    std::string Id;
    std::string Type;

    std::vector<std::unique_ptr<UIWidget>> Children;
};
