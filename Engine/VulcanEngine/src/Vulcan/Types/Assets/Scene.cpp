#include <fmt/color.h>
#include <Types/Assets/Scene.h>

#include <Types/Assets/AssetsManager.h>
#include <Entity.h>

#include "IRegistry.h"
#include "Components/NameComponent.h"
#include "Components/Transform.h"

#include "Reflection/ObjectManager.h" // Can delete this after making VAsset a reflected object

namespace fs = std::filesystem;

namespace VulcanEngine {

	Scene* Scene::FromJson(const std::string& InJson) {
		auto scene = VulcanCore::NewObject<Scene>();
		scene->Description = nlohmann::json::parse(InJson);
		return scene;
	}

	void Scene::ConstructJSON(const std::string_view& InPath) {
		fs::path Path{ InPath };
		AssetName = Path.stem().string();
		FilePath = std::move(Path.string()); // Reconstruct so we have to redo the replace
		std::replace(FilePath.begin(),FilePath.end(),'\\','/');

		auto& sceneJson = Description["Scene"];

		std::string sceneName = sceneJson["Name"];

		auto& entities = sceneJson["Entities"];

		for (auto& entity : entities) {
			const uint16_t id = entity["Id"];
			Entity* CreatedEntity = CreateEntity({ id,Registry});

			auto& components = entity["Components"];

			for (auto& component : components) {
				auto componentType = component["Type"].get<std::string>();

				if (auto* type = ComponentRegistry::Instance().Find(componentType)) {
					type->Creator(CreatedEntity, component["Properties"]);
				}
			}
			
			Entities.push_back(std::move(CreatedEntity));
		}
	}

	std::string Scene::ToJson() const {
		return Description.dump();
	}

	Entity* Scene::CreateEntity(const EntityConfig& Config) {
		return Entity::Create(Config);
	}

	void Scene::DestroyEntity(const Entity& entity) {
	}
	
}
