#include <Handlers/SpriteAssetHandler.h>
#include <fstream>
#include "Types/Assets/SpriteAsset.h"

namespace fs = std::filesystem;

namespace VulcanEngine {

    VAsset* SpriteAssetHandler::Load(const std::string& InPath) {
        std::string metaPath = fs::path(InPath).replace_extension(".vasset").string();
        std::ifstream file(metaPath, std::ios::binary);

        std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), {});
        file.close();

        SpriteAsset* asset = SpriteAsset::Create(InPath);
        asset->ConstructBinary(buffer);
        
        return asset;
    }

    TVector<VAsset*> SpriteAssetHandler::LoadAll(const std::string& InExtension) {
        TVector<VAsset*> assets{};
        
        for (const auto& entry : fs::directory_iterator("assets/")) { // No read inside directories for now
            if (entry.is_regular_file() && entry.path().extension() == InExtension) {
                auto asset = Load(entry.path().string());
                if (asset) {
                    assets.push_back(asset);
                }
            }
        }
        
        return assets;
    }

    void SpriteAssetHandler::Save(const std::string& InPath, const VAsset& InAsset) {
        auto metaPath = fs::path(InPath).replace_extension(".vasset");
        
        if (SpriteAsset* spriteAsset = VulcanCore::Cast<SpriteAsset>(const_cast<VAsset*>(&InAsset))) {
            std::ofstream file(metaPath,std::ios::binary);
            file << *spriteAsset;  
            file.close();
        }
        
    }

    void SpriteAssetHandler::CreateDefaultMetadata(const std::string& MetaPath, const std::string& ObjPath) {
        SpriteAsset spriteAsset{ObjPath};
        
        spriteAsset.GUID = VAsset::GenerateGUID();
        spriteAsset.AssetName = ObjPath.substr(ObjPath.find_last_of("/") + 1, ObjPath.find_last_of(".") - ObjPath.find_last_of("/") - 1);

        std::ofstream file(MetaPath,std::ios::binary);
        file << spriteAsset;    
        file.close();

    }
}
