#pragma once
#include <CoreAPI/precomp.h>

#include <SDL_rect.h>
#include <SDL_render.h>
#include <clay/clay.h>

#include "CoreAPI/VRenderer.h"

class UIClayRendererBase {

public:
    UIClayRendererBase(const VRenderer* InRenderer);
    virtual ~UIClayRendererBase() = default;
    
    void Render(const Clay_RenderCommandArray& Commands);
    virtual void DrawCommand(const Clay_RenderCommand& Command) = 0;
protected:
    SDL_FRect ToRect(const Clay_BoundingBox& Box) const;

    const VRenderer* Renderer;
};
