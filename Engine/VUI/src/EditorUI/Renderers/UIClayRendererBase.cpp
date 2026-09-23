#include <EditorUI/Renderers/UIClayRendererBase.h>

UIClayRendererBase::UIClayRendererBase(const VRenderer* InRenderer) : Renderer(InRenderer) {
   
}

SDL_FRect UIClayRendererBase::ToRect(const Clay_BoundingBox& Box) const {
    SDL_FRect Rect;
    Rect.x = Box.x;
    Rect.y = Box.y;
    Rect.w = Box.width;
    Rect.h = Box.height;
    
    return Rect;
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