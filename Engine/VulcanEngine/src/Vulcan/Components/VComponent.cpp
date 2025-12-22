#include <Components/VComponent.h>
#include <imgui.h>
#include <memory>
#include <Entity.h>
#include <VDrawHelper.h>
#include <CoreAPI/VCore.h>

namespace VulcanEngine {
	
	VComponent::VComponent(const VComponent& Component) {
	}

	VComponent::VComponent(VComponent&& Component) noexcept {
		
	}

	VComponent& VComponent::operator=(VComponent&& Component) noexcept {
		return *this;
	}

}