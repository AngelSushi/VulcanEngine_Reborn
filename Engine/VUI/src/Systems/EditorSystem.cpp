
#include <Systems/EditorSystem.h>

#include "ThemeAsset.h"
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

#include <clay/clay.h>  


#include <EditorUI/Backend/Clay/ClayBackend.h>

#include "FileManager.h"
#include "VPath.h"
#include "EditorUI/Core/Components/Button.h"
#include "EditorUI/Runtime/WidgetApplication.h"
#include "EditorUI/Core/UINodeResolver.h"
#include "EditorUI/Core/Components/Text.h"
#include "EditorUI/Core/Panels/CanvasPanel.h"
#include "EditorUI/Core/Panels/HorizontalBox.h"

DEFINE_LOG_CATEGORY(EditorUI);

EditorUIGlobals EditorSystem::Globals{};

EditorSystem::EditorSystem() {
    Game::GetFrameBeginEvent().Register(this,&EditorSystem::OnPreFrame,MEDIUM);
    Game::GetFrameEndEvent().Register(this,&EditorSystem::OnPostFrame,MEDIUM);

    /*
     * Have to change to StartupModule VUI, but for now as we have no module system, we can initialize the json's schema here
     */

    JsonManager::Get().GenerateAll("Intermediate/Schemas");
}

void EditorSystem::InitSystem() {
    Globals.Builder.emplace(Globals.Registry);
    
    RegisterSystemWidgets();
    RegisterSystemScreens();
}

void EditorSystem::RegisterSystemWidgets() {
    auto& Registry = Globals.Registry;

    // WWidget is a base class for all widgets, so we don't need to register it directly. 
    /*Registry.AddEntry("WWidget", UIRegisteredType{
        .Schemas = {
            // Define any schemas for WWidget properties here
        },
        .Create = []() -> std::unique_ptr<UIWidget> {
            return std::make_unique<WWidget>();
        }
    });*/

    Registry.AddEntry("CanvasPanel", UIRegisteredType{
        .Schemas = {
            // Define any schemas for CanvasPanel properties here
        },
        .Create = []() -> std::unique_ptr<UIWidget> {
            return std::make_unique<CanvasPanel>();
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

    Registry.AddEntry("HorizontalBox", UIRegisteredType{
        .Schemas = {
            // Define any schemas for Navbar properties here
        },
        .Create = []() -> std::unique_ptr<UIWidget> {
            return std::make_unique<HorizontalBox>();
        }
    });

    Registry.AddEntry("Text", UIRegisteredType{
        .Schemas = {
            // Define any schemas for Text properties here
        },
        .Create = []() -> std::unique_ptr<UIWidget> {
            return std::make_unique<Text>();
        }
    });
}

void EditorSystem::RegisterSystemScreens() {
    //AddWidget(std::make_unique<MainWindowNavbarScreen>()->Build());
}

void EditorSystem::StartSystem() {
    VSystem::StartSystem();
    
    Window = &VCore::GetInstance().GetWindow("VulcanEngine");
    Renderer = &VCore::GetInstance().GetRenderer("VulcanEngine");
    
    Globals.ClayBackend = new ClayBackend(Renderer);
    Globals.ClayBackend->Initialize(Window->GetSize().first,Window->GetSize().second);

    World::GetWorld().LoadScene(std::string("SampleLevel.vscene"));

    if (!Globals.Builder.has_value())
    {
        // Cant build UI widgets without a builder, log error
        return;
    }

    std::vector<std::string> NodesAssetsPath = FileManager::Get().LoadExtension("assets/",".vui");

   // RedirectLogSystem();

    for (auto& NodePath : NodesAssetsPath) {
        std::vector<uint8_t> Content = FileManager::Get().Read(NodePath);
        
        auto [Node,Success] = JsonSerializer::Load<UINode>(std::string(Content.begin(),Content.end()));

        if (!Success)
        {
            // Message error
            continue;
        }
        
       UINodeResolver Resolver(fs::path(NodePath).parent_path().string());
       Node = Resolver.Resolve(Node);
       AddWidget(Node);
    }

    
    WidgetApplication::Get().InitApp(Window,Renderer,EditorAssets);
} 

void EditorSystem::AddWidget(const UINode& Node) {
    std::unique_ptr<UIWidget> Widget = Globals.Builder->Build(Node,&Globals.PrevCache,&Globals.NextCache);
    if (Widget) {
        EditorAssets.push_back(std::move(Widget));
    }
    else {
        VLOG_ERROR(EditorUI,"Failed to build UI widget from node with ID: {}", Node.Id);
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
    
    // Maybe useless DeltaTime here 
    WidgetApplication::Get().Tick(DeltaTime);
}

void EditorSystem::OnPostFrame() {
    
}

void EditorSystem::Shutdown() {
    Globals.ClayBackend->Shutdown();
}

    

