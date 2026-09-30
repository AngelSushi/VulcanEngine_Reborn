#include <EditorUI/Runtime/WidgetApplication.h>

#include "Systems/EditorSystem.h"

void WidgetApplication::InitApp(const VWindow* InAppWindow,const VRenderer* InAppRenderer,std::vector<std::unique_ptr<UIWidget>>& InAppWidgets) {
    AppWindow = InAppWindow;
    AppRenderer = InAppRenderer;
    AppWidgets = &InAppWidgets;
    AppBackend = EditorSystem::GetGlobals().ClayBackend;

    for (const auto& Widget : *AppWidgets) {
        Widget->Initialized(*this);
    }
}

void WidgetApplication::Tick(float DeltaTime) {
    BeginFrame();
    BuildUI();
    EndFrame();

    // Maybe we can make a dirty flag or event to avoid resolving layout every frame, but for now we can resolve layout every frame for simplicity.
    for (const auto& Widget : *AppWidgets) {
        Widget->ResolveLayout();
    }
    
    ResolveInteraction();
    Draw();
}

VMath::Rect WidgetApplication::GetCurrentWindowGeometry() const {
    if (AppWindow) {
        const auto [Width,Height] = AppWindow->GetSize();
        return VMath::Rect(VMath::Vector2f(Width / 2.0f, Height / 2.0f), VMath::Vector2f(Width, Height));
    }

    return VMath::Rect(VMath::Vector2f::Zero(),VMath::Vector2f::Zero());
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
      /*  for (const auto& Child : Widget->GetChildren())
        {
            if (PerformInteraction(Child,MousePos)) {
                bHasChildFocused = true;
            }
        }
*/
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
        
    /*if (Widget->GetBounds().Contains(MousePos)) {
        if (FocusedWidget != Widget.get()) {
            return TryFocus(Widget.get());
        }

        return true;
    }*/
    if (FocusedWidget == Widget.get()) {
        FocusedWidget->NativeOnFocusLost();
        FocusedWidget = nullptr;
        return false;
    }

    return false;
}

void WidgetApplication::Draw() {
    AppRenderer->SetDrawColor(0,0,0,255);
    AppRenderer->Clear();
    
    AppBackend->GetClayRenderer()->Render(Commands);

    AppRenderer->SetDrawColor(0,0,0,255);
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
