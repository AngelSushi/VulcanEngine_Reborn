#pragma once
#include <Handlers/IAssetHandler.h>

namespace VulcanEngine {
    class SpriteAssetHandler : public IAssetHandler {
    public:
        VAsset* Load(const std::string& InPath) override;
        TVector<VAsset*> LoadAll(const std::string& InExtension) override;
        void Save(const std::string& InPath, const VAsset& InAsset) override;
        void CreateDefaultMetadata(const std::string& MetaPath, const std::string& ObjPath) override;
    };
}
