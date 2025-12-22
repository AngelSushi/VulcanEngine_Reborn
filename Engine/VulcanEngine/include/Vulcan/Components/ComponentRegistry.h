#pragma once
#include <Export.h>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

#include "LogSystem.h"
#include "Systems/EditorSystem.h"
#include <Entity.h>


namespace VulcanEngine {
	class VULCAN_ENGINE_API ComponentRegistry {
	public:
		static ComponentRegistry& Instance() {
			static ComponentRegistry instance;
			return instance;
		}
		
		template<typename T>
		void RegisterType(const std::string& name) {
			auto creator = [](Entity* entity, const nlohmann::json& json) {
				if (entity && !entity->HasComponent<T>()) {
					T& comp = entity->AddComponent<T>();
					comp.LoadComponent(json);
				}
				else {
					VLOG_WARN(EditorUI, "You are trying to add a component that already exists on the entity.");
				}
			};

			if (Registry.find(name) != Registry.end())
				return; 

			ComponentType compType { name, typeid(T), creator };
			Registry.emplace(name, compType); 
		}

		ComponentType* Find(const std::string& name) {
			auto it = Registry.find(name);
			return it != Registry.end() ? &it->second : nullptr; 
		}

		std::unordered_map<std::string, ComponentType>& GetRegistry() {
			return Registry;
		}
		
	private:
		std::unordered_map<std::string,ComponentType> Registry;
	};
}

