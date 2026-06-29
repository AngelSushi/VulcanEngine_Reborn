#include <EditorUI/Core/UINodeResolver.h>

#include "IO/FileManager.h"

UINodeResolver::UINodeResolver(std::string InBasePath) : BasePath(InBasePath) {
}

UINode UINodeResolver::Resolve(UINode& Node) {
    if (!HasRedirects(Node))
    {
        return Node;
    }

    std::vector<std::string> Redirects;
    for (UINode& Child : Node.Children) {
        UINode RedirectNode = LoadAndParse(fs::path(BasePath + "/" +  Child.Redirect).string());
        UINode::Merge(RedirectNode, Child);

        for (UINode& RedirectChild : RedirectNode.Children) {
            UINodeResolver LocalResolver(fs::path(BasePath + "/" +  Child.Redirect).parent_path().string());
            RedirectChild = Resolve(RedirectChild);
        }

        Child = RedirectNode;
    }

    return Node;
}

UINode UINodeResolver::LoadAndParse(const std::string& Path) {
    if (VulcanCore::FileManager::Get().Load(Path)) {
        std::vector<uint8_t> Content = VulcanCore::FileManager::Get().Read(Path);
        if (Content.size() > 0) {
            std::string JsonContent(Content.begin(), Content.end());
            auto [Node,Success] = VulcanEngine::JsonSerializer::Load<UINode>(JsonContent);

            if (Success) {
                return Node;
            }
        }
    }

    return UINode();
}

bool UINodeResolver::HasRedirects(const UINode& Node) {
    for (const UINode& Child : Node.Children) {
        if (!Child.Redirect.empty()) {
            return true;
        }
    }

    return false;
}
