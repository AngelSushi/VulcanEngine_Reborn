#pragma once
#include <CoreAPI/precomp.h>

#include <SDL_rect.h>
#include <SDL_render.h>
#include <clay/clay.h>

class UIClayRendererBase {

public:
    UIClayRendererBase(SDL_Renderer* InRenderer);
    virtual ~UIClayRendererBase() = default;
    
    void Render(const Clay_RenderCommandArray& Commands);
    virtual void DrawCommand(const Clay_RenderCommand& Command) = 0;
protected:
    SDL_FRect ToRect(const Clay_BoundingBox& Box) const;
    void SetColor(SDL_Renderer* Renderer, const Clay_Color& Color) const;

    SDL_Renderer* Renderer;
};