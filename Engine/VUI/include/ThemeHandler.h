#pragma once
#include <string>

#include <Handlers/IAssetHandler.h>

namespace VUI {

    class ThemeHandler : public IAssetHandler {

    public:
        // IAssetHandler interface
        VAsset* Load(const std::string& path);
        TVector<VAsset*> LoadAll(const std::string& extension);
        void Save(const std::string& path, const VAsset& asset);
        void CreateDefaultMetadata(const std::string& MetaPath,const std::string& ObjPath) override;
    };
}
