
#include <EditorUI/Core/Components/Text.h>

#include "Systems/FontSystem.h"

void Text::ApplyProps() {
    UIWidget::ApplyProps();

    std::string FontName = Node->TryPropValue("font").Get<std::string>();
    int FontSize = Node->TryPropValue("fontSize").Get<int>();

    FontId = FontSystem::Instance().GetFontId(FontName,FontSize);
    
    TextContent = Node->TryPropValue("text").Get<std::string>();
    TextColor = VulcanEngine::VColor(Node->TryPropValue("color").Get<std::string>());
}

void Text::Render(UIRenderContext& InContext) const {
    const Clay_ElementDeclaration Declaration = Build();

    if (Visibility == EWidgetVisibility::Collasped || Visibility == EWidgetVisibility::Hidden) {
        return;
    }

    Clay_TextElementConfig Config = {};
    Config.fontId = static_cast<uint16_t>(FontId);
    //Config.fontSize = 16;
    
    CLAY_TEXT(Clay_String(TextContent.data()),&Config);
}
