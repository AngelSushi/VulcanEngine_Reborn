#pragma once
#include <CoreAPI/precomp.h>

#include "CoreAPI/VRenderer.h"
#include "EditorUI/Backend/Clay/ClayBackend.h"
#include "EditorUI/Core/UIWidget.h"

class WidgetApplication {

public:
    void InitApp(VulcanEngine::VWindow* InAppWindow, VulcanEngine::Graphics::VRenderer* InAppRenderer,std::vector<std::unique_ptr<UIWidget>>& InAppWidgets);
    void Tick(float DeltaTime);

    static bool IsPointInside(VMath::Vector2f Point, VMath::Vector2f RectPos, VMath::Vector2f RectSize);

private:
    void BeginFrame();
    void BuildUI();
    void EndFrame();
    void ResolveInteraction();
    void Draw();

    
    VulcanEngine::VWindow* AppWindow;
    VulcanEngine::Graphics::VRenderer* AppRenderer;
    ClayBackend* AppBackend;

    // To define what really own UIWidget and how to manage the lifetime of UIWidget, we can either use unique_ptr or shared_ptr.
    std::vector<std::unique_ptr<UIWidget>>* AppWidgets;

    Clay_RenderCommandArray Commands;
};
