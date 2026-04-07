
#include <Systems/EditorSystem.h>

#include "ThemeAsset.h"
#include "Requests/UIRequests.h"
#include <Game.h>
#include <IRegistry.h>
#include <LogRedirectBuffer.h>

#include <Systems/RenderSystem.h>
#include <Types/Assets/AssetsManager.h>

#include <IO/JSON/JsonSerializer.h>
#include "World.h"
#include <EditorUI/Runtime/UIRenderContext.h>

#include <EditorUI/Core/UINode.h>

#include <EditorUI/Core/UIWidget.h>
#include "IO/FileManager.h"

#include <clay/clay.h>  

#include <EditorUI/Core/Components/WWidget.h>

#include <EditorUI/Backend/Clay/ClayBackend.h>

#include "EditorUI/Core/Components/Button.h"
#include "EditorUI/Runtime/WidgetApplication.h"

#include <CoreAPI/VRenderer.h>

DEFINE_LOG_CATEGORY(EditorUI);


namespace VulcanEngine {
    VulcanEngine::EditorUIGlobals VulcanEngine::EditorSystem::Globals{};
    
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
        auto& Registry = Globals.Registry;

        Registry.AddEntry("WWidget", UIRegisteredType{
            .Schemas = {
                // Define any schemas for WWidget properties here
            },
            .Create = []() -> std::unique_ptr<UIWidget> {
                return std::make_unique<WWidget>();
            }
        });

        Registry.AddEntry("Button", UIRegisteredType{
            .Schemas = {
                // Define any schemas for WWidget properties here
            },
            .Create = []() -> std::unique_ptr<UIWidget> {
                return std::make_unique<Button>();
            }
        });
    }

    void EditorSystem::StartSystem() {
        VSystem::StartSystem();
        
        Window = &VulcanCore::VCore::GetInstance().GetWindow("VulcanEngine");
        Renderer = &VulcanCore::VCore::GetInstance().GetRenderer("VulcanEngine");
        
        Globals.ClayBackend->Initialize(Window->GetSize().first,Window->GetSize().second);

        World::GetWorld().LoadScene(std::string("SampleLevel.vscene"));

        std::vector<std::string> EditorAssetsContent = VulcanCore::FileManager::ReadAllAssets(".vui");
        std::vector<UINode> NodeAssets;
        JsonSerializer::LoadAll<UINode>(EditorAssetsContent,NodeAssets);
  
       // RedirectLogSystem();

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

        WidgetApplication WApplication;
        
        WApplication.InitApp(Window,Renderer,EditorAssets);
        
        // Maybe useless DeltaTime here 
        WApplication.Tick(DeltaTime);
    }
    
    void EditorSystem::OnPostFrame() {
        
    }

    void EditorSystem::Shutdown() {
        Globals.ClayBackend->Shutdown();
    }

    
}
