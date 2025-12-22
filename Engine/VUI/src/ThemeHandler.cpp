#include <fstream>
#include <fmt/color.h>

#include <ThemeAsset.h>
#include <Themehandler.h>

namespace fs = std::filesystem;
namespace VUI {
    VulcanEngine::VAsset* ThemeHandler::Load(const std::string& InPath) {
        std::ifstream file(InPath);
        std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        auto asset = ThemeAsset::FromJson(json);
        asset->ConstructJSON(InPath);
        
        return asset;
    }

    VulcanEngine::TVector<VulcanEngine::VAsset*> ThemeHandler::LoadAll(const std::string& InExtension) {
        VulcanEngine::TVector<VulcanEngine::VAsset*> assets{};
        
        for (const auto& entry : fs::directory_iterator("assets/theme")) { // No read inside directories for now
            if (entry.is_regular_file() && entry.path().extension() == InExtension) {
                auto asset = Load(entry.path().string());
                if (asset) {
                    assets.push_back(asset);
                }
            }
        }

        return assets;
    }

    void ThemeHandler::Save(const std::string& InPath, const VulcanEngine::VAsset& InAsset) {
        std::ofstream file(InPath);
        file << InAsset.ToJson();
    }

    void ThemeHandler::CreateDefaultMetadata(const std::string& MetaPath, const std::string& ObjPath)
    {
    }
}
