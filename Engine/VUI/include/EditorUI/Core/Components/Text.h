#pragma once
#include <CoreAPI/precomp.h>

#include <EditorUI/Core/UIWidget.h>

class Text : public UIWidget {

public:
    void ApplyProps() override;
    void Render(UIRenderContext& InContext) const override;

private:
    std::string TextContent;

    // Maybe replace with VFont or something like that after
    int FontId;
    VulcanEngine::VColor TextColor;
};
