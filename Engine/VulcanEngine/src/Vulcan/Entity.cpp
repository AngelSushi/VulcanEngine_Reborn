#include <Entity.h>
#include <fmt/core.h>

#include "IRegistry.h"
#include "Components/NameComponent.h"

namespace VulcanEngine {
	
	Entity::Entity(const EntityConfig& Config) : Registry(Config.Registry) {
		Native = Registry.create();
		ID = Config.ID;
	}

	Entity::Entity(Entity&& MoveEntity) noexcept : Native(std::move(MoveEntity.Native)), Registry(MoveEntity.Registry)
                                               , ID(MoveEntity.ID) {
		fmt::println("Constructeur par mouvement d'Entity");
	}

	Entity& Entity::operator=(Entity&& MoveEntity) noexcept {
		fmt::println("Affectation par mouvement d'Entity");

		Native = std::move(MoveEntity.Native);
		//std::swap(_Entity, MoveEntity._Entity);
		
		ID = MoveEntity.ID;
		Registry = std::move(MoveEntity.Registry);
		
		return *this;
	}

	const std::string Entity::GetName() {
		return HasComponent<NameComponent>() ? GetComponent<NameComponent>().Name : "New Entity";
	}


	Entity::~Entity() {
		if (Native != entt::null && Registry.valid(Native)) {
			Registry.destroy(Native);
		}
	}

}
