    #pragma once
#include <CoreAPI/precomp.h>

#include "CoreAPI/VRenderer.h"
#include "EditorUI/Backend/Clay/ClayBackend.h"
#include "EditorUI/Core/UIWidget.h"

class WidgetApplication {

public:

    static WidgetApplication& Get() {
        static WidgetApplication instance;
        return instance;
    }
    
    void InitApp(const VulcanEngine::VWindow* InAppWindow,const VulcanEngine::Graphics::VRenderer* InAppRenderer,std::vector<std::unique_ptr<UIWidget>>& InAppWidgets);
    void Tick(float DeltaTime);

    void AddOverlay(const UINode& InNode);


private:
    void BeginFrame();
    void BuildUI();
    void EndFrame();
    void ResolveInteraction();
    bool PerformInteraction(const std::unique_ptr<UIWidget>& Widget,const VMath::Vector2f& MousePos);
    void Draw();
    
    bool TryFocus(UIWidget* InFocusWidget);
    const VulcanEngine::VWindow* AppWindow;
    const VulcanEngine::Graphics::VRenderer* AppRenderer;
    ClayBackend* AppBackend;

    // EditorSystem owns the widgets; WidgetApplication only holds a non-owning pointer to the list.
    std::vector<std::unique_ptr<UIWidget>>* AppWidgets = nullptr;

    // Represents all the UI elements that can't be attached to a widget parent, but can be drawn on top of the UI (e.g popup,notification etc).
    std::vector<UIWidget*> Overlays;
    
    UIWidget* FocusedWidget = nullptr;

    Clay_RenderCommandArray Commands;
};
