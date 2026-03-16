#include <EditorUI/Backend/ClayBackend.h>

ClayBackend::ClayBackend(SDL_Renderer* Renderer) {
    #if SDL_RENDERER
        SDLClayRenderer = new UIClaySDLRenderer(Renderer);
    #endif
}

void ClayBackend::Initialize(float Width, float Height) {
    int64 MemSize = Clay_MinMemorySize();
    Clay_Dimensions LayoutDimensions = { .width = Width, .height = Height };

    Arena.resize(MemSize);
    
    Clay_Arena ClayArena = Clay_CreateArenaWithCapacityAndMemory(MemSize,Arena.data());
    Clay_Initialize(ClayArena,LayoutDimensions,Clay_ErrorHandler{});
}

void ClayBackend::Shutdown() {
    Arena.clear();
}

void ClayBackend::BeginFrame(float Width, float Height) {
    Clay_BeginLayout();
}

Clay_RenderCommandArray ClayBackend::EndFrame() {
    return Clay_EndLayout();
}

UIClayRendererBase* ClayBackend::GetClayRenderer() const {
    #if SDL_RENDERER
        return SDLClayRenderer;
    #else
        return nullptr;
    #endif
    
}


