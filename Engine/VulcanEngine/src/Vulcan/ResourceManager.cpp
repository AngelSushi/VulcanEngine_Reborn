#include <ResourceManager.h>
#include "CoreAPI/VTexture.h"
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

#include "CoreAPI/VCore.h"
#include "CoreAPI/VSurface.h"
#include <Types/Assets/AssetsManager.h>



namespace fs = std::filesystem;

namespace VulcanEngine::Resources {
    
    ResourceManager::ResourceManager() {
        
    }
    
     std::shared_ptr<Graphics::VSurface> ResourceManager::LoadImage(const std::string& InPath) {
        auto it = SurfaceCache.find(InPath);
        if (it != SurfaceCache.end()) {
           return it->second;
        }

        auto surface = Graphics::VSurface::LoadFromFile(InPath);
        SurfaceCache[InPath] = surface;
        return surface;
    }

     std::shared_ptr<Graphics::VTexture> ResourceManager::GetTexture(const std::string& FilePath, Graphics::VRenderer& Renderer) {
        auto it = TextureCache.find(FilePath);
        if (it != TextureCache.end()) {
            return it->second;
        }

        auto surface = LoadImage(FilePath);

        auto texture = Graphics::VTexture::CreateFromSurface(Renderer, *surface, FilePath);
        TextureCache[FilePath] = texture;
        return texture;
    }
    
    const std::shared_ptr<Graphics::VTexture>& ResourceManager::GetTextureByName(const std::string& Name) {
        static std::shared_ptr<Graphics::VTexture> nullTex = nullptr;
        
        for (const auto& [path, tex] : TextureCache) {
            if (fs::path(path).filename() == Name) {
                return tex;
            }
        }

        return nullTex;
    }

    void ResourceManager::Purge() {
    }
}
