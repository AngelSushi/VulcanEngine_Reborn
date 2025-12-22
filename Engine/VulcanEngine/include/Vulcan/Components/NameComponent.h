#pragma once
#include <Export.h>
#include <Components/VComponent.h>
#include <string>
#include <typeindex>
#include <Types/VColor.h>
#include "Reflection/VMacros.h"
#include "ComponentRegistry.h"

#include <NameComponent.vht.h>


namespace VulcanEngine {
	class NameComponent;
	
	REGISTER_COMPONENT(NameComponent)

	VCLASS()
	class VULCAN_ENGINE_API NameComponent : public VComponent {
		friend class Entity;
		
		VCLASS_BODY()
		
	public:
		
		// Constructors
		NameComponent(std::string InName = "New Entity");
		NameComponent(const NameComponent& Component);
		NameComponent(NameComponent&& Component) noexcept;

		// Operators
		NameComponent& operator=(const NameComponent& Component) = delete;
		NameComponent& operator=(NameComponent&& Component) noexcept;

		// Getters
		const std::string& GetName() { return Name; }
		
		// VComponent's Functions
		std::string GetComponentName() override {
			return "NameComponent";
		} 

		void LoadComponent(const nlohmann::json& json) override;
		void SaveComponent(std::vector<std::uint8_t>& ByteArray) override;

		// Destructors
		~NameComponent() = default;

	private:
		VPROPERTY(InputText,meta=[onchange_func=World::BuildTree])
		std::string Name;
		
	};
}

