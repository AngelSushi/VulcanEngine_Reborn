
#include <EditorUI/Core/Components/Text.h>

#include "Systems/FontSystem.h"

void Text::ApplyProps() {
    UIWidget::ApplyProps();

    std::string FontName = Node.TryPropValue("font").Get<std::string>();
    FontSize = Node.TryPropValue("fontSize").Get<int>();

    FontId = FontSystem::Instance().GetFontId(FontName,FontSize);
    
    TextContent = Node.TryPropValue("text").Get<std::string>();
    TextColor = VColor(Node.TryPropValue("color").Get<std::string>());

    // Horizontal Alignment
}

void Text::BuildConfig() {
    Config.fontId = static_cast<uint16_t>(FontId);
    Config.fontSize = FontSize;
    Config.textColor = Clay_Color{ TextColor.R() * 255.f,TextColor.G() * 255.f,TextColor.B() * 255.f,TextColor.A() * 255.f};
    Config.textAlignment = CLAY_TEXT_ALIGN_CENTER;
}

void Text::BuildString() {
    String.length = (int)TextContent.size();
    String.chars = TextContent.c_str();
}

void Text::Render(UIRenderContext& InContext) {
    if (Visibility == EWidgetVisibility::Collasped || Visibility == EWidgetVisibility::Hidden) {
        return;
    }

    BuildString();
    BuildConfig();

    CLAY_TEXT(String,&Config);
}
