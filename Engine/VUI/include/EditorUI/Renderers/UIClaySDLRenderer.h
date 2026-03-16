#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Renderers/UIClayRendererBase.h>

class UIClaySDLRenderer : public UIClayRendererBase {

public:
#if SDL_RENDERER
    UIClaySDLRenderer(SDL_Renderer* InRenderer) : UIClayRendererBase(InRenderer) {}
    void DrawCommand(const Clay_RenderCommand& Command) override;
#endif
};