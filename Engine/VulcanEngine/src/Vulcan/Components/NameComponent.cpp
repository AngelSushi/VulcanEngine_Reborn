#include <Components/NameComponent.h>
#include <imgui.h>
#include <VDrawHelper.h>
#include <fmt/core.h>

#include <Types/Assets/AssetsManager.h>

#include "IRegistry.h"
#include "Reflection/VMacros.h"
namespace VulcanEngine {
	
	NameComponent::NameComponent(std::string InName) : Name(InName) {
	}

	NameComponent::NameComponent(const NameComponent& Component) {
		Name = Component.Name;
	}

	NameComponent::NameComponent(NameComponent&& MoveName) noexcept {
		Name = std::move(MoveName.Name);
	}

	NameComponent& NameComponent::operator=(NameComponent&& MoveName) noexcept {
		Name = std::move(MoveName.Name);

		return *this;
	}

	void NameComponent::LoadComponent(const nlohmann::json& json) {
		Name = json["Name"].get<std::string>();
	}

	void NameComponent::SaveComponent(std::vector<std::uint8_t>& ByteArray) {
//		AssetsManager::Instance().Serialize<const std::string&>(ByteArray, _Name);
	}
	
}
