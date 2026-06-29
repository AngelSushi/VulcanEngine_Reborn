
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

#include "EditorUI/Core/UINodeResolver.h"
#include "EditorUI/Core/Components/Navbar.h"
#include "EditorUI/Core/Components/NavButton.h"
#include "EditorUI/Core/Components/Text.h"
#include "EditorUI/Screens/MainWindowNavbarScreen.h"


namespace VulcanEngine {

    DEFINE_LOG_CATEGORY(EditorUI);
    
    VulcanEngine::EditorUIGlobals VulcanEngine::EditorSystem::Globals{};
    
    EditorSystem::EditorSystem() {
        Game::GetFrameBeginEvent().Register(this,&EditorSystem::OnPreFrame,MEDIUM);
        Game::GetFrameEndEvent().Register(this,&EditorSystem::OnPostFrame,MEDIUM);
    }

    void EditorSystem::InitSystem() {
        Globals.Builder.emplace(Globals.Registry);

        auto& Renderer = VulcanCore::VCore::GetInstance().GetRenderer("VulcanEngine");
        Globals.ClayBackend = new ClayBackend(Renderer.GetRenderer());

        RegisterSystemWidgets();
        RegisterSystemScreens();
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

        Registry.AddEntry("NavButton", UIRegisteredType{
            .Schemas = {
                // Define any schemas for NavButton properties here
            },
            .Create = []() -> std::unique_ptr<UIWidget> {
                return std::make_unique<NavButton>();
            }
        });

        Registry.AddEntry("Navbar", UIRegisteredType{
            .Schemas = {
                // Define any schemas for Navbar properties here
            },
            .Create = []() -> std::unique_ptr<UIWidget> {
                return std::make_unique<Navbar>();
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
        AddWidget(std::make_unique<MainWindowNavbarScreen>()->Build());
    }

    void EditorSystem::StartSystem() {
        VSystem::StartSystem();
        
        Window = &VulcanCore::VCore::GetInstance().GetWindow("VulcanEngine");
        Renderer = &VulcanCore::VCore::GetInstance().GetRenderer("VulcanEngine");
        
        Globals.ClayBackend->Initialize(Window->GetSize().first,Window->GetSize().second);

        World::GetWorld().LoadScene(std::string("SampleLevel.vscene"));

        if (!Globals.Builder.has_value())
        {
            // Cant build UI widgets without a builder, log error
            return;
        }

        std::vector<std::string> NodesAssetsPath = VulcanCore::FileManager::Get().LoadExtension("assets/",".vui");

       // RedirectLogSystem();

        for (auto& NodePath : NodesAssetsPath) {
            std::vector<uint8_t> Content = VulcanCore::FileManager::Get().Read(NodePath);
            
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

        Globals.WApplication = WidgetApplication();
        Globals.WApplication.InitApp(Window,Renderer,EditorAssets);
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
        Globals.WApplication.Tick(DeltaTime);
    }
    
    void EditorSystem::OnPostFrame() {
        
    }

    void EditorSystem::Shutdown() {
        Globals.ClayBackend->Shutdown();
    }

    
}
