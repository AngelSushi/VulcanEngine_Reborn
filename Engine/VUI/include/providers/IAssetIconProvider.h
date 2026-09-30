#pragma once
#include <any>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <fmt/format.h>
#include <Entries/TreeEntry.h>
#include "ITreeIconProvider.h"
#include "CoreAPI/VSurface.h"
#include <ResourceManager.h>

#include <filesystem>

#include "VCast.h"
#include "Types/Assets/AssetsManager.h"
#include "Types/Assets/Scene.h"

namespace fs = std::filesystem;

namespace VUI {
    
    class IAssetIconProvider : public ITreeIconProvider {
    public:
        std::string GetName() const override { return "IAssetIconProvider"; }
        
        std::shared_ptr<VTexture> GetIconForEntry(const TreeEntry& InEntry) const override {
            if (InEntry.IsDirectory) {
                return ResourceManager::Instance().GetTextureByName("folder.png");
            }

            auto assetInfo = std::any_cast<AssetsManager::AssetInfo>(InEntry.Payload);

            fs::path path(assetInfo.FullPath);
            
            if (path.extension().string() == ".vscene") {
                return ResourceManager::Instance().GetTextureByName("scene.png");
            }

            if (path.extension().string() == ".ttf") { // Modify wheen VFont will be implemented
                return ResourceManager::Instance().GetTextureByName("font.png");
            }
    
            auto availableExt = VSurface::GetAvailableExtensions();
        
            if (std::find(availableExt.begin(),availableExt.end(), path.extension().string()) != availableExt.end()) {
                auto tex = ResourceManager::Instance().GetTextureByName(InEntry.EntryName);

                if (tex) {
                    return tex;
                }
            }
            
            return ResourceManager::Instance().GetTextureByName("miss.png");
        }
    };
}
