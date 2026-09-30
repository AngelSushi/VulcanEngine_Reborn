#pragma once
#include <CoreAPI/precomp.h>

#include "UINode.h"


class UINodeBuilder {

public:
    UINodeBuilder(std::string Type, std::string Id);

    UINodeBuilder& Window(int InWindowIndex);
    UINodeBuilder& Prop(std::string Key, UIValue Value);
    UINodeBuilder& Children(UINodeBuilder ChildNodeBuilder);

    
    UINode Build();

private:
    int WindowIndex;
    std::string Type;
    std::string Id;

    std::unordered_map<std::string, UIValue> Values;
    std::vector<UINode> ChildrenNodes;
};
