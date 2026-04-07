#include <iostream>
#include <EditorUI/Renderers/UIClaySDLRenderer.h>

// Need maybe the #if SDL_RENDERER guard here as well, but for now we can assume this file is only compiled when SDL_RENDERER is defined.

void UIClaySDLRenderer::DrawCommand(const Clay_RenderCommand& Command) {
    switch (Command.commandType) {
        default:
            break;
        case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
            SDL_FRect Rect = ToRect(Command.boundingBox);
            SetColor(Renderer,Command.renderData.rectangle.backgroundColor);
            SDL_RenderFillRectF(Renderer, &Rect);
            break;
    }
}
