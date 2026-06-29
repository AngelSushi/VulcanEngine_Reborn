
#include <EditorUI/Renderers/UIClaySDLRenderer.h>

#include "Systems/FontSystem.h"
// Need maybe the #if SDL_RENDERER guard here as well, but for now we can assume this file is only compiled when SDL_RENDERER is defined.

void UIClaySDLRenderer::DrawCommand(const Clay_RenderCommand& Command) {
    SDL_FRect Rect = ToRect(Command.boundingBox);
    
    switch (Command.commandType) {
        default:
            break;
        case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
            SetColor(Renderer,Command.renderData.rectangle.backgroundColor);
            SDL_RenderFillRectF(Renderer, &Rect);
            break;

        case CLAY_RENDER_COMMAND_TYPE_TEXT:
            int fontId = Command.renderData.text.fontId;
            int fontSize = Command.renderData.text.fontSize;

            TTF_Font* Font = FontSystem::Instance().GetFont(fontId,fontSize);
            if (!Font) {
                // Log Error
                return;
            }

            SDL_Color TextColor = SDL_Color( Command.renderData.text.textColor.r, Command.renderData.text.textColor.g, Command.renderData.text.textColor.b, Command.renderData.text.textColor.a);
            SDL_Surface* TextSurface = TTF_RenderUTF8_Blended(Font,Command.renderData.text.stringContents.chars,TextColor);
            SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer,TextSurface);

            SDL_RenderCopyF(Renderer, TextTexture, NULL, &Rect);

            // Maybe not , cache it ? 
            SDL_FreeSurface(TextSurface);
            SDL_DestroyTexture(TextTexture);
            
            break;
    }
}
