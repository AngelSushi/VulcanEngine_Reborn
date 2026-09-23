#pragma once
#include <Export.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <CoreAPI/VTexture.h>

#include "CoreAPI/VCore.h"

#include <ResourceManager.vht.h>



class VRenderer;

VCLASS()
class VULCAN_ENGINE_API ResourceManager : public VulcanCore::VObject {

    VCLASS_BODY()
    
public:

    VFUNCTION()
    static ResourceManager& Instance() {
        static ResourceManager instance;
        return instance;
    }
    
    ResourceManager();
    ~ResourceManager() = default;

    std::shared_ptr<VSurface> LoadImage(const std::string& InPath);

    std::shared_ptr<VTexture> GetTexture(const std::string& InPath);
    std::shared_ptr<VTexture> GetTexture(const std::string& InPath,const VRenderer& InRenderer);
    const std::shared_ptr<VTexture>& GetTextureByName(const std::string& Name);

    void Purge();

    
private:
    std::map<std::string,std::shared_ptr<VSurface>> SurfaceCache{};
    std::map<std::string,std::shared_ptr<VTexture>> TextureCache{};
    
};


