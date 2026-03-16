#include <EditorUI/Renderers/UIClayRendererBase.h>

UIClayRendererBase::UIClayRendererBase(SDL_Renderer* InRenderer) : Renderer(InRenderer) {
}

SDL_FRect UIClayRendererBase::ToRect(const Clay_BoundingBox& Box) const {
    return SDL_FRect{ .x = Box.x, .y = Box.y, .w = Box.width, .h = Box.height};
}

void UIClayRendererBase::SetColor(SDL_Renderer* Renderer, const Clay_Color& Color) const {
    SDL_SetRenderDrawColor(Renderer, (uint8)Color.r, (uint8)Color.g, (uint8)Color.b, (uint8)Color.a);
}


void UIClayRendererBase::Render(const Clay_RenderCommandArray& Commands) {
    if (!Renderer) {
        return;
    }

    for (auto& Command : Commands) {
        DrawCommand(Command);
    }
}