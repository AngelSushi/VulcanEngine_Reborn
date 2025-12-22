#include <Handlers/UIAssetHandler.h>
#include <fstream>
#include <fmt/color.h>

#include <Types/Assets/UIAsset.h>
namespace fs = std::filesystem;

namespace VulcanEngine {

    VAsset* UIAssetHandler::Load(const std::string& InPath) {
        
        std::ifstream file(InPath);
        std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        auto asset = UIAsset::FromJson(json);
        
        asset->ConstructJSON(InPath);
        return asset;
    }

    TVector<VAsset*> UIAssetHandler::LoadAll(const std::string& InExtension) {
        TVector<VAsset*> assets{};

        
        for (const auto& entry : fs::directory_iterator("assets/ui")) { // No read inside directories for now
            if (entry.is_regular_file() && entry.path().extension() == InExtension) {
                auto asset = Load(entry.path().string());
                assets.push_back(asset);
            }
        }

        return assets;
    }

    void UIAssetHandler::Save(const std::string& InPath, const VAsset& InAsset) {
        std::ofstream file(InPath);
        file << InAsset.ToJson();
    }

    void UIAssetHandler::CreateDefaultMetadata(const std::string& MetaPath,const std::string& ObjPath)
    {
    }
}
