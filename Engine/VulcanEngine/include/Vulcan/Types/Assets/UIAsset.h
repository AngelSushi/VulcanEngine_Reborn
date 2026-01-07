#pragma once
#include <nlohmann/json.hpp>

#include <VUIWindow.h>

#include <LogSystem.h>
#include <Types/Assets/VAsset.h>

#include <Renderables/VUIRenderable.h>


DECLARE_LOG_CATEGORY(UI);
namespace VulcanEngine {
    
    class UIAsset : public VAsset {
        
    public:

        static UIAsset* FromJson(const std::string& InJson);
        std::string ToJson() const override;

        void ConstructJSON(const std::string_view& InPath) override;
        void Show();
        void Hide();

        const VUI::VUIWindow& GetWindow() const { return Window; }

    private:
        void BuildWindowFlags(ImGuiWindowFlags& OutFlags) const;
        void ApplyWindowLayout() const;
        void DrawUI(ImGuiWindowFlags InWindowFlags);
        
        std::pair<float,float> GetPosition(const ImVec2& DisplaySize) const;
        std::pair<float,float> GetSize(const ImVec2& DisplaySize) const;
        VUI::VUIWindow Window{};
        std::vector<std::unique_ptr<VUI::VUIRenderable>> Renderables{};
    };
}
