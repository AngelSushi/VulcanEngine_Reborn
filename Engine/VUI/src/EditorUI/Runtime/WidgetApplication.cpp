#include <EditorUI/Runtime/WidgetApplication.h>

#include "Systems/EditorSystem.h"

void WidgetApplication::InitApp(VulcanEngine::VWindow* InAppWindow,VulcanEngine::Graphics::VRenderer* InAppRenderer,std::vector<std::unique_ptr<UIWidget>>& InAppWidgets) {
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
    for (auto& Widget : *AppWidgets) {
        //UIRenderContext Ctx = MakeRenderContext();
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

    std::cout << "Mouse Position: (" << MousePos.x << ", " << MousePos.y << ")\n";
    
    // Maybe needd to be in world and not local space ? 
    for (auto& Widget : *AppWidgets) {
        if (IsPointInside(MousePos, Widget->GetPosition(), Widget->GetSize())) {
            std::cout << "Mouse is inside widget with ID: " << Widget->GetID() << "\n";
        }
    }
}


void WidgetApplication::Draw() {
    SDL_SetRenderDrawColor(AppRenderer->GetRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(AppRenderer->GetRenderer());
        
    AppBackend->GetClayRenderer()->Render(Commands);

    SDL_SetRenderDrawColor(AppRenderer->GetRenderer(), 0, 0, 0, 255);
}

bool WidgetApplication::IsPointInside(VMath::Vector2f Point, VMath::Vector2f RectPos, VMath::Vector2f RectSize) {
    return Point.x >= RectPos.x && Point.x <= RectPos.x + RectSize.x &&
           Point.y >= RectPos.y && Point.y <= RectPos.y + RectSize.y;
}