#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UIWidget.h>

class Text : public UIWidget {

public:
    void ApplyProps() override;
    Clay_ElementDeclaration Build() override;
    void Render(UIRenderContext& InContext) override;

private:
    void BuildConfig();
    void BuildString();
    
    std::string TextContent;

    // Maybe replace with VFont or something like that after
    uint16_t FontId = -1;
    uint16_t FontSize = -1;
    VColor TextColor;

    bool bDrawBorder = false;
    VColor BorderColor;

    Clay_String String = {};
    Clay_TextElementConfig Config = {};
};
