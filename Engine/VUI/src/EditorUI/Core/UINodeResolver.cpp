#include <EditorUI/Core/UINodeResolver.h>

#include "FileManager.h"

UINodeResolver::UINodeResolver(std::string InBasePath) : BasePath(InBasePath) {
}

UINode UINodeResolver::Resolve(UINode& Node) {
    bool bIsSelf = false;
    
    if (!HasRedirects(Node,bIsSelf)) {
        return Node;
    }

    if (bIsSelf) {
        UINode SelfNode = LoadAndParse(fs::path(BasePath + "/" +  Node.Redirect).string());
        UINode::Merge(SelfNode, Node);

        Node = SelfNode;
    }

    // Maybe LocalResolver should take the path of RedirectNode
    for (UINode& Child : Node.Children) {
        bool bIsChildSelf = false;
        fs::path ChildPath = BasePath + "/" + Child.Redirect;

        if (HasRedirects(Child,bIsChildSelf)) {
            UINode RedirectNode = LoadAndParse(ChildPath.string());
            UINode::Merge(RedirectNode, Child);
            Child = RedirectNode;
        }
        
        for (UINode& RedirectChild : Child.Children) {
            UINodeResolver LocalResolver(ChildPath.parent_path().string());
            RedirectChild = LocalResolver.Resolve(RedirectChild);
        }
    }

    return Node;
}

UINode UINodeResolver::LoadAndParse(const std::string& Path) {
    if (FileManager::Get().Exists(Path)) {
        std::vector<uint8_t> Content = FileManager::Get().Read(Path);
        if (Content.size() > 0) {
            std::string JsonContent(Content.begin(), Content.end());
            auto [Node,Success] = JsonSerializer::Load<UINode>(JsonContent);

            if (Success) {
                return Node;
            }
        }
    }

    return UINode();
}

bool UINodeResolver::HasRedirects(const UINode& Node,bool& bOutIsSelf) {
    for (const UINode& Child : Node.Children) {
        if (!Child.Redirect.empty()) {
            return true;
        }
    }

    bOutIsSelf = !Node.Redirect.empty();
    return bOutIsSelf;
}
