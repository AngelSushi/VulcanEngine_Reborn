#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UIWidget.h>

class Text : public UIWidget {

public:
    void ApplyProps() override;
    void Render(UIRenderContext& InContext) override;

private:
    void BuildConfig();
    void BuildString();
    
    std::string TextContent;

    // Maybe replace with VFont or something like that after
    uint16_t FontId = -1;
    uint16_t FontSize = -1;
    VColor TextColor;

    Clay_String String = {};
    Clay_TextElementConfig Config = {};
};
