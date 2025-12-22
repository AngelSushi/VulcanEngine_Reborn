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
        
        std::shared_ptr<VulcanEngine::Graphics::VTexture> GetIconForEntry(const TreeEntry& InEntry) const override {
            if (InEntry.IsDirectory) {
                return VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName("folder.png");
            }

            auto assetInfo = std::any_cast<VulcanEngine::AssetsManager::AssetInfo>(InEntry.Payload);

            fs::path path(assetInfo.FullPath);
            
            if (path.extension().string() == ".vscene") {
                return VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName("scene.png");
            }

            if (path.extension().string() == ".ttf") { // Modify wheen VFont will be implemented
                return VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName("font.png");
            }
    
            auto availableExt = VulcanEngine::Graphics::VSurface::GetAvailableExtensions();
        
            if (std::find(availableExt.begin(),availableExt.end(), path.extension().string()) != availableExt.end()) {
                auto tex = VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName(InEntry.EntryName);

                if (tex) {
                    return tex;
                }
            }
            
            return VulcanEngine::Resources::ResourceManager::Instance().GetTextureByName("miss.png");
        }
    };
}
