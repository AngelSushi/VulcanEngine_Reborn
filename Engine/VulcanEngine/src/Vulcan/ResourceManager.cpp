#include <ResourceManager.h>
#include "CoreAPI/VTexture.h"
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>

#include "CoreAPI/VCore.h"
#include "CoreAPI/VSurface.h"
#include <Types/Assets/AssetsManager.h>



namespace fs = std::filesystem;

    
ResourceManager::ResourceManager() {
    
}

 std::shared_ptr<VSurface> ResourceManager::LoadImage(const std::string& InPath) {
    auto it = SurfaceCache.find(InPath);
    if (it != SurfaceCache.end()) {
       return it->second;
    }

    auto surface = VSurface::LoadFromFile(InPath);
    SurfaceCache[InPath] = surface;
    return surface;
}

std::shared_ptr<VTexture> ResourceManager::GetTexture(const std::string& InPath) {
    return GetTexture(InPath, VCore::GetInstance().GetRenderer("VulcanEngine"));
}

std::shared_ptr<VTexture> ResourceManager::GetTexture(const std::string& FilePath,const VRenderer& Renderer) {
    auto it = TextureCache.find(FilePath);
    if (it != TextureCache.end()) {
        return it->second;
    }

    auto surface = LoadImage(FilePath);

    auto texture = VTexture::CreateFromSurface(Renderer, *surface, FilePath);
    TextureCache[FilePath] = texture;
    return texture;
}

const std::shared_ptr<VTexture>& ResourceManager::GetTextureByName(const std::string& Name) {
    static std::shared_ptr<VTexture> nullTex = nullptr;
    
    for (const auto& [path, tex] : TextureCache) {
        if (fs::path(path).filename() == Name) {
            return tex;
        }
    }

    return nullTex;
}

void ResourceManager::Purge() {
}

