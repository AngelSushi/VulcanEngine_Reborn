#include <EditorUI/Core/UINodeBuilder.h>

UINodeBuilder::UINodeBuilder(std::string Type, std::string Id) : Type(Type), Id(Id), WindowIndex(0) {}

UINodeBuilder& UINodeBuilder::Window(int InWindowIndex) {
    WindowIndex = InWindowIndex;
    return *this;
}

UINodeBuilder& UINodeBuilder::Prop(std::string Key, UIValue Value) {
    Values[Key] = Value;
    return *this;
}

UINodeBuilder& UINodeBuilder::Children(UINodeBuilder ChildNodeBuilder) {
    ChildrenNodes.push_back(ChildNodeBuilder.Build());
    return *this;
}

UINode UINodeBuilder::Build() {
    UINode Node;
    Node.Type = Type;
    Node.Id = Id;
    Node.WindowIndex = WindowIndex;
    Node.Properties = Values;
    Node.Children = ChildrenNodes;

    return Node;
}

