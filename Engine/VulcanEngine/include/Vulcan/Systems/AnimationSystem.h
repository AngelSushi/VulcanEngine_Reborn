#pragma once
#include <Export.h>

#include "VSystem.h"

namespace VulcanEngine {
	class VULCAN_ENGINE_API AnimationSystem : public VSystem {

	public:
		// Constructors
		AnimationSystem() : VSystem() {}
		AnimationSystem(bool isActive, bool isEditorSystem) : VSystem(isActive, isEditorSystem) {}


		// VSystem's Functions
		virtual void InitSystem() override;
		virtual void StartSystem() override;
		virtual void Iterate(float DeltaTime) override;

	private:
		float _AnimTimer;
	};
}

