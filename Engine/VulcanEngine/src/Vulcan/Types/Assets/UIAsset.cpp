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

namespace VulcanEngine {
    UIAsset::UIAsset() : Cache(), OutRoot(nullptr) {
    }
    
    void UIAsset::ConstructJson(const std::string_view& InPath) {
       // Construct OutNode from Json
        
<<<<<<< Updated upstream
        
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
=======
>>>>>>> Stashed changes
    }
    
    void UIAsset::Show() {
        if (!ImGui::GetCurrentContext()) {
            fmt::print(fg(fmt::color::red), "ImGui context is not initialized. Cannot render UIAsset.\n");
            return;
        }


    }

    void UIAsset::Hide() {
    }

    void UIAsset::Build(const UIRegistry& InRegistry, const UIBuilder& InBuilder) {
        Cache.Clear();

<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
        

        PrevCache = std::move(Cache);
        
<<<<<<< Updated upstream
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
=======
>>>>>>> Stashed changes
    }

    void UIAsset::BuildFromNode(const UINode& RootNode) {

        OutRoot = 
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
