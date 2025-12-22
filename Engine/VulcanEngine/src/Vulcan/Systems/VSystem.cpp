#include <Systems/VSystem.h>
#include <fmt/core.h>

namespace VulcanEngine {

	VSystem::VSystem() : _IsActive(true),_IsEditorSystem(false),_LastActive(true) {
	
	}

	VSystem::VSystem(bool IsActive,bool IsEditorSystem) : _IsActive(IsActive),_IsEditorSystem(IsEditorSystem),_LastActive(IsActive) {
		
	}

	VSystem::VSystem(VSystem&& MoveSystem) noexcept {
		_IsActive = MoveSystem._IsActive;
		_LastActive = MoveSystem._LastActive;
		_LastActive = MoveSystem._LastActive;
	}

	VSystem& VSystem::operator=(VSystem&& MoveSystem) noexcept {
		_IsActive = MoveSystem._IsActive;
		_LastActive = MoveSystem._LastActive;
		_IsEditorSystem = MoveSystem._IsEditorSystem;
		return *this;
	}

	void VSystem::InitSystem() {}

	void VSystem::StartSystem() {}

	void VSystem::Iterate(float DeltaTime) {}

	void VSystem::Shutdown() {}

	void VSystem::SetActive(bool IsActive) {
		_IsActive = IsActive;

		if (_IsActive && !_LastActive) {
			StartSystem();
		}

		_LastActive = _IsActive;
	}

	VSystem::~VSystem() {}
}
