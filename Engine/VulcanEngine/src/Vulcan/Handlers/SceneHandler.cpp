#include <Handlers/SceneHandler.h>
#include <fstream>

#include <Types/Assets/Scene.h>
namespace fs = std::filesystem;

namespace VulcanEngine {

    VAsset* SceneHandler::Load(const std::string& InPath) {
        std::ifstream file(InPath);
        std::string json((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        auto scene = Scene::FromJson(json);
        scene->ConstructJSON(InPath);
        
        return scene;
    }

    TVector<VAsset*> SceneHandler::LoadAll(const std::string& InExtension) {
        TVector<VAsset*> assets{};
        
        for (const auto& entry : fs::directory_iterator("assets/scenes")) { // No read inside directories for now
            if (entry.is_regular_file() && entry.path().extension() == InExtension) {
                auto asset = Load(entry.path().string());
                if (asset) {
                    assets.push_back(asset);
                }
            }
        }
        
        return assets;
    }

    void SceneHandler::Save(const std::string& InPath, const VAsset& InAsset) {
        std::ofstream file(InPath);
        file << InAsset.ToJson();
    }

    void SceneHandler::CreateDefaultMetadata(const std::string& MetaPath, const std::string& ObjPath)
    {
    }
}
