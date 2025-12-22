#pragma once
#include <string>

#include "TVector.h"
#include "Types/Assets/VAsset.h"

namespace VulcanEngine {
    class IAssetHandler {
        
    public:
        virtual ~IAssetHandler() = default;

        virtual VAsset* Load(const std::string& path) = 0;
        virtual TVector<VAsset*> LoadAll(const std::string& extension) = 0;
        virtual void Save(const std::string& path, const VAsset& asset) = 0;
        virtual void CreateDefaultMetadata(const std::string& MetaPath,const std::string& ObjPath) = 0;
    };
}
