#pragma once
#include <string>

#include <Handlers/IAssetHandler.h>

namespace VUI {

    class ThemeHandler : public VulcanEngine::IAssetHandler {

    public:
        // IAssetHandler interface
        VulcanEngine::VAsset* Load(const std::string& path);
        VulcanEngine::TVector<VulcanEngine::VAsset*> LoadAll(const std::string& extension);
        void Save(const std::string& path, const VulcanEngine::VAsset& asset);
        void CreateDefaultMetadata(const std::string& MetaPath,const std::string& ObjPath) override;
    };
}
