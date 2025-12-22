#include <imgui_internal.h>
#include <Systems/EditorSystem.h>

#include "ThemeAsset.h"
#include "Requests/UIRequestRenderer.h"
#include "Requests/UIRequests.h"
#include <Game.h>
#include <IRegistry.h>
#include <LogRedirectBuffer.h>

#include "Renderables/VUIFactory.h"
#include <Systems/RenderSystem.h>
#include <Types/Assets/AssetsManager.h>

#include "World.h"
#include "Requests/ImportAssetRenderer.h"

DEFINE_LOG_CATEGORY(EditorUI);


namespace VulcanEngine{
    EditorSystem::EditorSystem() {
        auto& window = VulcanCore::VCore::GetInstance().GetWindow("VulcanEngine");
        auto& renderer = VulcanCore::VCore::GetInstance().GetRenderer("VulcanEngine");

        GUIRenderer = ImGuiRenderer::Create({
            .Window = window,
            .Renderer = renderer
        });

        Game::GetFrameBeginEvent().Register(this,&EditorSystem::OnPreFrame,MEDIUM);
        Game::GetFrameEndEvent().Register(this,&EditorSystem::OnPostFrame,MEDIUM);
    }

    void EditorSystem::InitSystem() {
            
    }

    void EditorSystem::StartSystem() {
        VSystem::StartSystem();

        World::GetWorld().LoadScene(std::string("SampleLevel.vscene"));
        
        EditorAssets = AssetsManager::Instance().LoadAll<UIAsset>(".vui");
        
        std::sort(EditorAssets.begin(), EditorAssets.end(),[](UIAsset* a, const UIAsset* b) {
            return a->GetWindow().ZIndex < b->GetWindow().ZIndex;
        });
        
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(0, 0);
        style.IndentSpacing = 60.0f;

        ImGuiIO& io = ImGui::GetIO();

        ImFont* font = io.Fonts->AddFontFromFileTTF("assets/fonts/Recta.ttf", 14.0f);
        
        io.Fonts->Build();

        io.FontDefault = font;

        auto& renderer = VUI::UIRequestRenderer::Instance();
        renderer.RegisterRenderer(VUI::UIRequestType::ImportAsset, std::make_unique<VUI::ImportAssetRenderer>());
        
        RedirectLogSystem();
    }
    
    void EditorSystem::OnPreFrame() {
        GUIRenderer->NewFrame();
    }

    void EditorSystem::Iterate(float DeltaTime) {
        VSystem::Iterate(DeltaTime);

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::ShowDemoWindow();
        ImGui::ShowStyleEditor();
        
        SetupDockspace();

        if (auto* request = VUI::UIRequests::Instance().Current()) {
            VUI::UIRequestRenderer::Instance().Render(*request);
        }
        
        
        for (auto& asset : EditorAssets) {
            if (asset) {
                asset->Show();
            }
            else {
                fmt::print(fmt::fg(fmt::color::red), "[EditorSystem] Null UIAsset encountered in EditorAssets\n");
            }
        }

        
        static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGuiID dockspace_id = ImGui::GetID("DockspaceID");

            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id,ImGuiDockNodeFlags_NoWindowMenuButton);
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

            ImGuiID dock_left,dock_mid, dock_right;
            dock_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, nullptr, &dock_right);
            dock_mid = ImGui::DockBuilderSplitNode(dock_right, ImGuiDir_Left, 0.65f, nullptr, &dock_right);

            ImGuiID dock_mid_top,dock_mid_bottom;
            dock_mid_top = ImGui::DockBuilderSplitNode(dock_mid, ImGuiDir_Up, 0.1f, nullptr, &dock_mid);
            dock_mid_bottom = ImGui::DockBuilderSplitNode(dock_mid, ImGuiDir_Down, 0.3f, nullptr, &dock_mid);

            ImGuiID dock_left_bottom;
            dock_left_bottom = ImGui::DockBuilderSplitNode(dock_left, ImGuiDir_Down, 0.5f, nullptr, &dock_left);
            
            ImGui::DockBuilderDockWindow("Toolbar", dock_mid_top);
            
            ImGui::DockBuilderDockWindow("Hierarchy", dock_left);
            ImGui::DockBuilderDockWindow("Scene View", dock_mid);
            ImGui::DockBuilderDockWindow("Game View", dock_mid);
            ImGui::DockBuilderDockWindow("Inspector", dock_right);
            ImGui::DockBuilderDockWindow("Console", dock_mid_bottom);
            ImGui::DockBuilderDockWindow("Assets", dock_left_bottom);

            ImGui::DockBuilderFinish(dockspace_id);
        }
        
    }
    
    void EditorSystem::SetupDockspace() {
        ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);

        // docking splitter size
        ImGui::PushStyleVar(ImGuiStyleVar_DockingSeparatorSize, 1.0f); 
        bool open = true;
        ImGui::Begin("Dockspace",&open, WindowFlags);
        
        ImGuiID dockspaceID = ImGui::GetID("DockspaceID");
        ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoWindowMenuButton);
        
        ImGui::End();
        ImGui::PopStyleVar();

    }
    
    void EditorSystem::OnPostFrame() {
        GUIRenderer->Render();
    }
    
}
