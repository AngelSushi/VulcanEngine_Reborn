#include <EditorUI/Renderers/UIClayRendererBase.h>

UIClayRendererBase::UIClayRendererBase(SDL_Renderer* InRenderer) : Renderer(InRenderer) {
}

SDL_FRect UIClayRendererBase::ToRect(const Clay_BoundingBox& Box) const {
    SDL_FRect Rect;
    Rect.x = Box.x;
    Rect.y = Box.y;
    Rect.w = Box.width;
    Rect.h = Box.height;
    
    return Rect;
}

void UIClayRendererBase::SetColor(SDL_Renderer* Renderer, const Clay_Color& Color) const {
    SDL_SetRenderDrawColor(Renderer, (uint8)Color.r, (uint8)Color.g, (uint8)Color.b, (uint8)Color.a);
}


void UIClayRendererBase::Render(const Clay_RenderCommandArray& Commands) {
    if (!Renderer) {
        return;
    }

    for (size_t i = 0; i < Commands.length; ++i) {
        const Clay_RenderCommand& Command = Commands.internalArray[i];
        DrawCommand(Command);
    }
}