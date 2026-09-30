
#include <EditorUI/Core/Components/Text.h>

#include "Systems/FontSystem.h"

void Text::ApplyProps() {
    UIWidget::ApplyProps();

    std::string FontName = Node.TryPropValue("font").Get<std::string>();
    FontSize = Node.TryPropValue("fontSize").Get<int>();

    FontId = FontSystem::Instance().GetFontId(FontName,FontSize);
    
    TextContent = Node.TryPropValue("text").Get<std::string>();
    TextColor = VColor(Node.TryPropValue("color").Get<std::string>());

    // Maybe have to do it in UIWidget class in future
    bDrawBorder = Node.TryPropValue("border").Get<bool>();
    BorderColor = VColor(Node.TryPropValue("borderColor").Get<std::string>());

    // Horizontal Alignment
}

Clay_ElementDeclaration Text::Build() {
    Clay_ElementDeclaration Declaration = UIWidget::Build(); 
    Declaration.border.color = BorderColor.ToClay();
    Declaration.border.width = CLAY_BORDER_OUTSIDE(1);
    
    return Declaration;
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
    const Clay_ElementDeclaration Declaration = Build();
    
    if (Visibility == EWidgetVisibility::Collasped || Visibility == EWidgetVisibility::Hidden) {
        return;
    }

    BuildString();
    BuildConfig();

    // Maybe have to change it with clay debug mode, but as its not implemented yet, we can use this for now to test the text rendering
    if (bDrawBorder) {
        CLAY(Clay_GetElementId(GetClayString()), Declaration) {
            CLAY_TEXT(String, &Config);
        }
    }
    else {
        CLAY_TEXT(String, &Config);
    }
}
