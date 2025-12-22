#pragma once
#include <Export.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <CoreAPI/VTexture.h>

#include "Entries/TreeEntry.h"
#include "CoreAPI/VCore.h"

#include <Resources/ResourceManager.vht.h>


namespace VulcanEngine::Resources {

    class VRenderer;

    VCLASS()
    class VULCAN_ENGINE_API ResourceManager : public VulcanCore::VObject {

        VCLASS_BODY()
        
    public:

        VFUNCTION()
        static VulcanEngine::Resources::ResourceManager& Instance() {
            static ResourceManager instance;
            return instance;
        }
        
        ResourceManager();
        ~ResourceManager() = default;

        std::shared_ptr<Graphics::VSurface> LoadImage(const std::string& InPath);
        std::shared_ptr<Graphics::VTexture> GetTexture(const std::string& InPath,Graphics::VRenderer& InRenderer = VulcanCore::VCore::GetInstance().GetRenderer("VulcanEngine"));
        const std::shared_ptr<Graphics::VTexture>& GetTextureByName(const std::string& Name);

        void Purge();

        
    private:
        std::map<std::string,std::shared_ptr<Graphics::VSurface>> SurfaceCache{};
        std::map<std::string,std::shared_ptr<Graphics::VTexture>> TextureCache{};
        
    };

}
