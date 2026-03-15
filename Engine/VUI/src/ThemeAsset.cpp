#include "ThemeAsset.h"
#include <nlohmann/json.hpp>

#include "Reflection/ObjectManager.h"

namespace VUI {
    void ThemeAsset::ConstructJson(const std::string_view& InPath) {
        // Load fonts

        std::filesystem::path Path{ InPath };
        AssetName = Path.stem().string();
        FilePath = std::move(Path.string()); // Reconstruct so we have to redo the replace
        std::replace(FilePath.begin(),FilePath.end(),'\\','/');
        
        DefaultFlags = Description.value("default_flags", nlohmann::json::object());
    }

    ThemeAsset* ThemeAsset::FromJson(const std::string& InJson) {
        auto Asset = VulcanCore::NewObject<ThemeAsset>();
        Asset->Description = nlohmann::json::parse(InJson);
        return Asset;
    }

    std::string ThemeAsset::ToJson() const {
        return Description.dump();
    }

    void ThemeAsset::Init() {
    }

    void ThemeAsset::Render() {
        

    }

    void ThemeAsset::PostRender() {
    }
}
