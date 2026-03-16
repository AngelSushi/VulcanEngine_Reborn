
#include <Systems/EditorSystem.h>

#include "ThemeAsset.h"
#include "Requests/UIRequestRenderer.h"
#include "Requests/UIRequests.h"
#include <Game.h>
#include <IRegistry.h>
#include <LogRedirectBuffer.h>

#include <Systems/RenderSystem.h>
#include <Types/Assets/AssetsManager.h>

#include "JsonSerializer.h"
#include "World.h"
#include <EditorUI/Runtime/UIRenderContext.h>

#include <EditorUI/Core/UINode.h>

#include <EditorUI/Core/UIWidget.h>
#include "IO/FileManager.h"

DEFINE_LOG_CATEGORY(EditorUI);


namespace VulcanEngine {
    EditorSystem::EditorSystem() {
        Game::GetFrameBeginEvent().Register(this,&EditorSystem::OnPreFrame,MEDIUM);
        Game::GetFrameEndEvent().Register(this,&EditorSystem::OnPostFrame,MEDIUM);
    }

    void EditorSystem::InitSystem() {
        RegisterSystemWidgets();
        Globals.Builder.emplace(Globals.Registry);

        auto& Renderer = VulcanCore::VCore::GetInstance().GetRenderer("VulcanEngine");
        Globals.ClayBackend = new ClayBackend(Renderer.GetRenderer());
    }
    
    void EditorSystem::RegisterSystemWidgets() {
    }

    void EditorSystem::StartSystem() {
        VSystem::StartSystem();
        
        auto& window = VulcanCore::VCore::GetInstance().GetWindow("VulcanEngine");
        auto size = window.GetSize();
        
        Globals.ClayBackend->Initialize(size.first,size.second);

        World::GetWorld().LoadScene(std::string("SampleLevel.vscene"));

        std::vector<std::string> EditorAssetsContent = VulcanCore::FileManager::ReadAllAssets(".vui");
        std::vector<UINode> NodeAssets;
        JsonSerializer::LoadAll<UINode>(EditorAssetsContent,NodeAssets);
  
        RedirectLogSystem();

        for (auto& Node : NodeAssets) {
           if (Globals.Builder.has_value()) {
               std::unique_ptr<UIWidget> Widget = Globals.Builder->Build(Node,&Globals.PrevCache,&Globals.NextCache);
                if (Widget) {
                     EditorAssets.push_back(std::move(Widget));
                }
                else {
                    VLOG_ERROR(EditorUI,"Failed to build UI widget from node with ID: {}", Node.Id);
                }
           }
        }
    }

    UIRenderContext EditorSystem::MakeRenderContext() {
        UIRenderContext Ctx;
        Ctx.GlobalVM = Globals.GlobalVM;
        Ctx.LocalVM = {};
        return Ctx;
    }
    
    void EditorSystem::OnPreFrame() {
        
    }

    void EditorSystem::Iterate(float DeltaTime) {
        VSystem::Iterate(DeltaTime);

        ClayBackend* BackEnd = Globals.ClayBackend;

        auto& window = VulcanCore::VCore::GetInstance().GetWindow("VulcanEngine");
        auto size = window.GetSize();
        
        BackEnd->BeginFrame(size.first,size.second);

        for (auto& Widget : EditorAssets) {
            UIRenderContext Ctx = MakeRenderContext();
            Widget->Render(Ctx);
        }

        Clay_RenderCommandArray Commands = BackEnd->EndFrame();

        BackEnd->GetClayRenderer()->Render(Commands);
    }
    
    void EditorSystem::OnPostFrame() {
        
    }

    void EditorSystem::Shutdown() {
        Globals.ClayBackend->Shutdown();
    }

    
}
