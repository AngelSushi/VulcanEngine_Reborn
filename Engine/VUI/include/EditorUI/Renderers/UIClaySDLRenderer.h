#pragma once
#include <CoreAPI/precomp.h>
#include <EditorUI/Renderers/UIClayRendererBase.h>

#include "CoreAPI/VSurface.h"

class UIClaySDLRenderer : public UIClayRendererBase {

public:
#if SDL_RENDERER
    UIClaySDLRenderer(const VRenderer* InRenderer) : UIClayRendererBase(InRenderer) {}
    void DrawCommand(const Clay_RenderCommand& Command) override;
#endif

private:
    std::shared_ptr<VSurface> TestSurface;
    std::shared_ptr<VTexture> TestTexture;
};
