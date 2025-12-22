#pragma once
#include <imgui.h>
#include <string>
#include <variant>

#include <Types/VFont.h>
#include <Types/Assets/VAsset.h>

#include <ThemeAsset.vht.h>

namespace VUI {

    VCLASS()
    class ThemeAsset : public VulcanEngine::VAsset {

        VCLASS_BODY()

    public:
        // Maybe need move semantics 
        ThemeAsset() = default;
        ThemeAsset(const ThemeAsset&) = default; 
        ThemeAsset& operator=(const ThemeAsset&) = default;

        
        void ConstructJSON(const std::string_view& InAssetName) override;

        static ThemeAsset* FromJson(const std::string& InJson);
        std::string ToJson() const override;

        void Init();
        void Render(ImGuiWindowFlags& OutFlags);
        void PostRender();

        
    private:
        std::vector<std::pair<ImGuiCol,ImVec4>> Colors{};
        std::vector<std::pair<ImGuiStyleVar,std::variant<float,ImVec2>>> StyleVars{};

        VulcanEngine::VFont TitleFont{};
        VulcanEngine::VFont BodyFont{};

        nlohmann::json DefaultFlags;
    };
}
