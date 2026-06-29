#include <EditorUI/Core/Components/NavButton.h>

#include "EditorUI/Core/UINodeResolver.h"
#include "EditorUI/Runtime/WidgetApplication.h"
#include "Systems/EditorSystem.h"

void NavButton::ApplyProps() {
    Button::ApplyProps();

    Action = Node->TryPropValue("action").Get<std::string>();
    auto SubmenuJson = Node->TryPropValue("submenu").Get<std::string>();

    auto [Node,Success] = VulcanEngine::JsonSerializer::Load<UINode>(SubmenuJson);

    if (!Success)
    {
        // Message error
        return;
    }

    // Resolver ? 
    SubMenuNode = Node;
}

void NavButton::Initialized(WidgetApplication& WidgetApplication) {
    Button::Initialized(WidgetApplication);

    OnFocus.Register(this,&NavButton::OnHoverFunc);
}

void NavButton::OnHoverFunc() {
    VulcanEngine::EditorSystem::Instance().AddWidget(SubMenuNode);
}
