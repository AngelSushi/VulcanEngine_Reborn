#pragma once
#include <nlohmann/json.hpp>
#include <Export.h>

#include <Entries/TreeEntry.h>
#include "Reflection/VObject.h"
#include "Systems/VSystem.h"
#include "Types/Assets/Scene.h"

#include <World.vht.h>

#include "TVector.h"


namespace fs = std::filesystem;

namespace VulcanEngine {

	VCLASS()
	class VULCAN_ENGINE_API World : public VulcanCore::VObject {

		VCLASS_BODY()
	public:

		VFUNCTION()
		static VulcanEngine::World& GetWorld() {
			static World world;
			return world;
		}

		VFUNCTION()
		static VulcanEngine::World& Instance() {
			return GetWorld();
		}

		World(const World&) = delete;
		World& operator=(const World&) = delete;
		~World() = default;
		


		void LoadScene(const std::string& SceneName);
		void LoadScene(const fs::path& ScenePath);

		Scene* GetCurrentScene() const {
			return CurrentScene;
		}
		
		void SetScene(Scene* Scene) {
			CurrentScene = Scene;
		}

		VUI::TreeEntry& GetEntities();
		TVector<std::string>& GetAvailableComponentsFor(Entity* Ent) const;
		
	private:
		World();

		VFUNCTION()
		void BuildTree();
		
		std::vector<std::unique_ptr<VSystem>> WorldSystems;
		Scene* CurrentScene; // Unique_ptr should be enough
		VUI::TreeEntry RootTree;
	};
}

