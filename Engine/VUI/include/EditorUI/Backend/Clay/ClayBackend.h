#pragma once

#include <CoreAPI/precomp.h>

#include "EditorUI/Renderers/UIClaySDLRenderer.h"

class ClayBackend {

public:
    ClayBackend(const VRenderer* Renderer);
    
    void Initialize(float Width,float Height);
    void Shutdown();
    
    void BeginFrame(float Width,float Height);
    Clay_RenderCommandArray EndFrame();

    UIClayRendererBase* GetClayRenderer() const;
    static Clay_Dimensions MeasureText(Clay_StringSlice Text,Clay_TextElementConfig* TextConfig, void* OutMetrics);


private:
    std::vector<uint8> Arena;

    UIClaySDLRenderer* SDLClayRenderer = nullptr;
};
