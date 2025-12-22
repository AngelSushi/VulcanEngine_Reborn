#pragma once
#include <nlohmann/json.hpp>
#include <Export.h>

#include <Types/Assets/VAsset.h>

#include <Entity.h>

#include "TVector.h"
#include <Scene.vht.h>

namespace VulcanEngine {        

	VCLASS()
	class VULCAN_ENGINE_API Scene : public VAsset {
		friend class World;

		VCLASS_BODY()
	public:

		Scene() = default;
		~Scene() = default;
		Scene(const Scene&) = default;
		Scene(Scene&&) noexcept = default;
		Scene& operator=(const Scene&) = default;
		Scene& operator=(Scene&&) noexcept = default;
		

		static Scene* FromJson(const std::string& InJson);
		void ConstructJSON(const std::string_view& InPath) override;
		std::string ToJson() const override;

		static std::vector<std::string> GetAvailableExtensions() {
			return { ".vscene" };
		}

		
		Entity* CreateEntity(const EntityConfig& Config);
		void DestroyEntity(const Entity& entity);


		const TVector<Entity*>& GetEntities() const {
			return Entities;
		}

		entt::registry& GetRegistry() {
			return Registry;
		}
		
	private:
		entt::registry Registry;
		TVector<Entity*> Entities; // Maybe weak_ptr ? 
	};
}

