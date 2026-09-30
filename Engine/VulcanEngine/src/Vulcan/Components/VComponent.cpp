#include <Components/VComponent.h>

VComponent::VComponent(const VComponent& Component) {
}

VComponent::VComponent(VComponent&& Component) noexcept {
	
}

VComponent& VComponent::operator=(VComponent&& Component) noexcept {
	return *this;
}

