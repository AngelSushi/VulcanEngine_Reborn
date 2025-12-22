#include <imgui.h>
#include <Types/Assets/UIAsset.h>

#include <SDL_stdinc.h>
#include <fmt/color.h>

#include "Layout.h"
#include "LogSystem.h"
#include "VUIHelper.h"
#include "Renderables/VUIFactory.h"
#include <IRegistry.h>

#include "Reflection/ObjectManager.h"

DEFINE_LOG_CATEGORY(UI);

namespace VulcanEngine{
    void UIAsset::ConstructJSON(const std::string_view& InPath) {
        std::filesystem::path Path{ InPath };
        AssetName = Path.stem().string();
        FilePath = std::move(Path.string()); // Reconstruct so we have to redo the replace
        std::replace(FilePath.begin(),FilePath.end(),'\\','/');
        
        
        Window.Name = Description["name"].get<std::string>();

        if (Description.contains("properties") && Description["properties"].is_object()) {
            Window.properties = Description["properties"];
        }

        Window.ZIndex = Description["z-index"].get<int>();

        const auto& themeName = Description.value("theme", "default");
        
        auto theme = ThemeRegistry.FindIf([&themeName](const VUI::ThemeAsset& t) {
           return t.GetName() == themeName;
        });
        
        Window.Theme = *theme; // Not sure if this is safe and no changes possible in runtime for themes
        Window.Theme.Init();
        
        for (auto& elementDesc : Description["elements"]) {
            VUI::VUIElement Element = {
                VUI::VUIHelper::json_or<std::string>(elementDesc, "type", ""),
                VUI::VUIHelper::json_or<std::string>(elementDesc, "label", ""),
                VUI::VUIHelper::json_or<std::string>(elementDesc, "bind", ""),
                VUI::VUIHelper::json_or<std::string>(elementDesc, "visible", ""),
                VUI::VUIHelper::json_or<std::string>(elementDesc, "onStateChanged", ""),
                {}
            };

            if (elementDesc.contains("properties")) {
                Element.Properties = elementDesc["properties"];
            }

            auto widget = VUI::VUIFactory::Create(Element);
            if (widget) {
                
                Renderables.push_back(std::move(widget));
                Window.Elements.push_back(std::move(Element));
            } else {
                VLOG_WARN(UI, "Unknown element type: {}", Element.Type);
            }
            
        }
    }
    
    void UIAsset::Show() {
        if (!ImGui::GetCurrentContext()) {
            fmt::print(fg(fmt::color::red), "ImGui context is not initialized. Cannot render UIAsset.\n");
            return;
        }
        
        ImGuiWindowFlags windowFlags = 0;
        
        BuildWindowFlags(windowFlags);
        ApplyWindowLayout();
        DrawUI(windowFlags);

    }

    void UIAsset::Hide() {
    }

    void UIAsset::BuildWindowFlags(ImGuiWindowFlags& OutFlags) const {
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties, "no_title_bar", false) ? ImGuiWindowFlags_NoTitleBar : 0;
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties, "no_resize", false) ? ImGuiWindowFlags_NoResize : 0;
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties,"no_move",false) ? ImGuiWindowFlags_NoMove : 0;
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties,"no_scrollbar",false) ? ImGuiWindowFlags_NoScrollbar : 0;
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties,"no_collapse",false) ? ImGuiWindowFlags_NoCollapse : 0;
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties,"always_auto_resize",false) ? ImGuiWindowFlags_AlwaysAutoResize : 0;
        OutFlags |= VUI::VUIHelper::json_or<bool>(Window.properties,"no_docking",false) ? ImGuiWindowFlags_NoDocking : 0;
    }

    void UIAsset::ApplyWindowLayout() const {
        auto io = ImGui::GetIO();

        auto [x, y] = GetPosition(io.DisplaySize);
        ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);

        auto [w, h] = GetSize(io.DisplaySize);
        ImGui::SetNextWindowSize(ImVec2(w, h),ImGuiCond_Once);
    }

    void UIAsset::DrawUI(ImGuiWindowFlags InWindowFlags) {
        Window.Theme.Render(InWindowFlags);

        auto fontScale = VUI::VUIHelper::json_or<float>(Window.properties, "fontScale", 1.f);
        
        ImGui::GetIO().FontGlobalScale = fontScale;
        
        bool open = true;
        if (ImGui::Begin(Window.Name.c_str(), &open, InWindowFlags)) {
            Window.Size = ImGui::GetContentRegionAvail();
            
            const size_t n = std::min(Renderables.size(), Window.Elements.size());
            for (size_t i = 0; i < n; ++i) {
                auto* renderable = Renderables[i].get();
                if (!renderable) 
                    continue;

                
                 auto bindVisibilityMethod = VulcanEngine::BindingRegistry.FindIf([&](const VUI::Binding& b) {
                    return b.GetName() == Window.Elements[i].VisibilityBind;
                });

                if (bindVisibilityMethod) {
                    const bool& isVisible = bindVisibilityMethod ? bindVisibilityMethod->InvokeAs<bool>() : true;

                    if (!isVisible) {
                        continue;
                    }
                }

                VUI::UILayout layout{};
                renderable->Render(Window.Elements[i], layout);
            }
        }

        ImGui::End();
        
        Window.Theme.PostRender();
    }

    std::pair<float, float> UIAsset::GetPosition(const ImVec2& DisplaySize) const {
        float x = VUI::VUIHelper::json_or<float>(Window.properties, "x", 500.f);
        float y = VUI::VUIHelper::json_or<float>(Window.properties, "y", 200.f);

        if (x > 0 && x <= 1) x *= DisplaySize.x;
        if (y > 0 && y <= 1) y *= DisplaySize.y;

        return {x, y};
    }

    std::pair<float, float> UIAsset::GetSize(const ImVec2& DisplaySize) const {
        float width = VUI::VUIHelper::json_or<float>(Window.properties, "width", 400.f);
        float height = VUI::VUIHelper::json_or<float>(Window.properties, "height", 300.f);

        if (width > 0 && width <= 1) width *= DisplaySize.x;
        if (height > 0 && height <= 1) height *= DisplaySize.y;

        return {width, height};
    }

    UIAsset* UIAsset::FromJson(const std::string& InJson) {
        auto Asset = VulcanCore::NewObject<UIAsset>();
        Asset->Description = nlohmann::json::parse(InJson);
        return Asset;
    }

    std::string UIAsset::ToJson() const {
        return Description.dump();
    }
}
