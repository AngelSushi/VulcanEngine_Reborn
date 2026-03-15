#include <Components/VComponent.h>

namespace VulcanEngine {
	
	VComponent::VComponent(const VComponent& Component) {
	}

	VComponent::VComponent(VComponent&& Component) noexcept {
		
	}

	VComponent& VComponent::operator=(VComponent&& Component) noexcept {
		return *this;
	}

}