#include <EditorUI/Backend/Clay/ClayBackend.h>

#define CLAY_IMPLEMENTATION
#include <clay/clay.h>

#include "Systems/FontSystem.h"


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
    Clay_SetMeasureTextFunction(MeasureText,&FontSystem::Instance());
}

void ClayBackend::Shutdown() {
    Arena.clear();
}

void ClayBackend::BeginFrame(float Width, float Height) {
    Clay_SetLayoutDimensions(Clay_Dimensions { .width = Width, .height = Height });
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

Clay_Dimensions ClayBackend::MeasureText(Clay_StringSlice Text, Clay_TextElementConfig* TextConfig, void* UserData) {
    FontSystem* System = static_cast<FontSystem*>(UserData);

    TTF_Font* Font = System->GetFont(TextConfig->fontId);
    int w, h;

    TTF_SizeUTF8(Font,Text.chars,&w,&h);
    return Clay_Dimensions { .width = static_cast<float>(w), .height = static_cast<float>(h) };
}


