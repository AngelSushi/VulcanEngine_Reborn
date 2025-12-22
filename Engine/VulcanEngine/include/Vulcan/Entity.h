#pragma once
#include <Export.h>
#include <string>
#include <entt/entt.hpp>
#include <Components/VComponent.h>
#include <CoreAPI/VRenderer.h>

#include <Entity.vht.h>

namespace VulcanEngine {

	struct EntityConfig {
		uint16_t ID;
		entt::registry& Registry;
	};

	VCLASS()
	class VULCAN_ENGINE_API Entity : public VulcanCore::VObject {

		VCLASS_BODY()
	public:
		static Entity* Create(const EntityConfig& Config) {
			return VulcanCore::NewObject<Entity>(Config);
		}

		Entity(const EntityConfig& Config);
		Entity(const Entity&) = delete;
		Entity(Entity&&) noexcept;

		Entity& operator=(const Entity&) = delete;
		Entity& operator=(Entity&&) noexcept;

		// Getters
		const entt::registry& GetRegistry() const {
			return Registry;
		}

		const entt::entity& GetNative() const {
			return Native;
		}
		
		const int GetID() { return ID; }

		const std::string GetName();
		
		template<typename T,typename... Args>
		T& AddComponent(Args&&... args) {
			auto& component = Registry.emplace<T>(Native, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		bool HasComponent() const {
			return Registry.any_of<T>(Native);
		}

		template<typename T>
		T& GetComponent() {
			return Registry.get<T>(Native);
		}

		template<typename T>
		void RemoveComponent(VComponent* ComponentRef) {
			if (HasComponent<T>()) {
				Registry.remove<T>(Native);
			}
		}
			
		~Entity();

	private:
		entt::entity Native;
		entt::registry& Registry;
		uint16_t ID;

	};



}

