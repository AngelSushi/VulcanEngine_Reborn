
#include <EditorUI/Renderers/UIClaySDLRenderer.h>

#include "CoreAPI/VSurface.h"
#include "CoreAPI/VTexture.h"
#include "Systems/FontSystem.h"
// Need maybe the #if SDL_RENDERER guard here as well, but for now we can assume this file is only compiled when SDL_RENDERER is defined.

void UIClaySDLRenderer::DrawCommand(const Clay_RenderCommand& Command) {
    SDL_FRect Rect = ToRect(Command.boundingBox);
    
    switch (Command.commandType) {
        default:
            break;

        case CLAY_RENDER_COMMAND_TYPE_BORDER:
            {
                //Draw the border using the specified color and thickness
                Renderer->SetDrawColor(static_cast<uint8_t>(Command.renderData.border.color.r),
                        static_cast<uint8_t>(Command.renderData.border.color.g),
                        static_cast<uint8_t>(Command.renderData.border.color.b),
                        static_cast<uint8_t>(Command.renderData.border.color.a));

                Renderer->Catch(Renderer->RenderDrawRectF(Rect));
            
                break;
            }
        case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
            {
                Renderer->SetDrawColor(static_cast<uint8_t>(Command.renderData.rectangle.backgroundColor.r),
                    static_cast<uint8_t>(Command.renderData.rectangle.backgroundColor.g),
                    static_cast<uint8_t>(Command.renderData.rectangle.backgroundColor.b),
                    static_cast<uint8_t>(Command.renderData.rectangle.backgroundColor.a));

                Renderer->Catch(Renderer->RenderFillRectF(Rect));
                break;
            }
        case CLAY_RENDER_COMMAND_TYPE_TEXT:
            {
                int fontId = Command.renderData.text.fontId;
                int fontSize = Command.renderData.text.fontSize;

                TTF_Font* Font = FontSystem::Instance().GetFont(fontId,fontSize);
                if (!Font) {
                    // Log Error
                    return;
                }
        
                SDL_Color TextColor = SDL_Color( static_cast<Uint8>(Command.renderData.text.textColor.r),
                    static_cast<Uint8>(Command.renderData.text.textColor.g),
                    static_cast<Uint8>(Command.renderData.text.textColor.b),
                    static_cast<Uint8>(Command.renderData.text.textColor.a));

                std::string Text(Command.renderData.text.stringContents.chars, Command.renderData.text.stringContents.length);

                // GetFont et tout ce qui en suite ne devrait pas etre directement gérer par font System ??
                // Maybe on peut passer FontSystem par un Context, ou quelque chose du genre pour rendre la structure plus propre et claire ?  
                TestSurface = FontSystem::Instance().CreateUTF8BlendedSurface(Font, Text,TextColor);
                TestTexture = VTexture::CreateFromSurface(*Renderer,*TestSurface.get(),"");


                Renderer->Catch(Renderer->RenderCopyF(*TestTexture.get(),Rect));
            
                break;
            }
        case CLAY_RENDER_COMMAND_TYPE_IMAGE:
            {
                VTexture* Texture = static_cast<VTexture*>(Command.renderData.image.imageData);

                if (!Texture) {
                    break;
                }

                // Add teint

                Renderer->Catch(Renderer->RenderCopyF(*Texture,Rect));
                
                break;
            }
    }
}
