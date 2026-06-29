#include <EditorUI/Runtime/WidgetApplication.h>

#include "Systems/EditorSystem.h"

void WidgetApplication::InitApp(const VulcanEngine::VWindow* InAppWindow,const VulcanEngine::Graphics::VRenderer* InAppRenderer,std::vector<std::unique_ptr<UIWidget>>& InAppWidgets) {
    AppWindow = InAppWindow;
    AppRenderer = InAppRenderer;
    AppWidgets = &InAppWidgets;
    AppBackend = VulcanEngine::EditorSystem::GetGlobals().ClayBackend;
}

void WidgetApplication::Tick(float DeltaTime) {
    BeginFrame();
    BuildUI();
    EndFrame();
    ResolveInteraction();
    Draw();
}

void WidgetApplication::BeginFrame() {
    auto size = AppWindow->GetSize();
    AppBackend->BeginFrame(size.first,size.second);
}

void WidgetApplication::BuildUI() {
    // Do not make sort here, make a event at the end of ui builder. Its just for test&example
    std::sort(AppWidgets->begin(),AppWidgets->end(),[&](const std::unique_ptr<UIWidget>& A,const std::unique_ptr<UIWidget>& B) {
        return( A->Type != "NavBar") < (B->Type == "NavBar");
    });
    
    for (const auto& Widget : *AppWidgets) {
        UIRenderContext RenderContext;
        Widget->Render(RenderContext);
    }
}

void WidgetApplication::EndFrame() {
    Commands = AppBackend->EndFrame();
}

void WidgetApplication::ResolveInteraction() {
    VMath::Vector2i MousePos;
    SDL_GetMouseState(&MousePos.x,&MousePos.y);

    for (auto& Widget : *AppWidgets) {
        bool bHasChildFocused = false;
        for (const auto& Child : Widget->GetChildren())
        {
            if (PerformInteraction(Child,MousePos)) {
                bHasChildFocused = true;
            }
        }

        if (!bHasChildFocused) {
            PerformInteraction(Widget,MousePos);
        }
    }
}

// We make a copy with std::unique_ptr ? 
bool WidgetApplication::PerformInteraction(const std::unique_ptr<UIWidget>& Widget,const VMath::Vector2f& MousePos) {
    if (Widget->GetVisibility() != EWidgetVisibility::Visible || !Widget->SupportFocus()) {
        return false;
    }
        
    if (Widget->GetBounds().Contains(MousePos)) {
        if (FocusedWidget != Widget.get()) {
            return TryFocus(Widget.get());
        }

        return true;
    }
    else if (FocusedWidget == Widget.get()) {
        FocusedWidget->NativeOnFocusLost();
        FocusedWidget = nullptr;
        return false;
    }

    return false;
}

void WidgetApplication::Draw() {
    SDL_SetRenderDrawColor(AppRenderer->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(AppRenderer->GetRenderer());

    AppBackend->GetClayRenderer()->Render(Commands);

    SDL_SetRenderDrawColor(AppRenderer->GetRenderer(), 0, 0, 0, 255);
}

bool WidgetApplication::TryFocus(UIWidget* InFocusWidget) {
    if (FocusedWidget) {
        if (FocusedWidget != InFocusWidget) {
            if (InFocusWidget->NativeOnFocusReceived()) {
                FocusedWidget->NativeOnFocusLost();
                FocusedWidget = InFocusWidget;
                return true;
            }
        }
    }
    else {
        if (InFocusWidget->NativeOnFocusReceived()) {
            FocusedWidget = InFocusWidget;
            return true;
        }

        return false;
    }

    return false;
}
