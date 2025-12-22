#pragma once
#include <Export.h>
#include <Components/VComponent.h>
#include <memory>
#include <Types/Assets/Spritesheet.h>
#include <Components/ComponentRegistry.h>

#include <AnimationComponent.vht.h>

namespace VulcanEngine {

	class AnimationComponent;

	REGISTER_COMPONENT(AnimationComponent)
	
	VCLASS()
	class VULCAN_ENGINE_API AnimationComponent : public VComponent {
	
		VCLASS_BODY()
		
	public:

		// Constructors
		AnimationComponent() = default;
		AnimationComponent(std::unique_ptr<Graphics::Spritesheet>&&);
		AnimationComponent(const AnimationComponent&) = delete;
		AnimationComponent(AnimationComponent&&) noexcept;

		// Operators
		AnimationComponent& operator=(const AnimationComponent&);
		AnimationComponent& operator=(AnimationComponent&&) noexcept;

		void Play(std::string AnimName);
		void Stop();

		std::unique_ptr<Graphics::Spritesheet::Animation>& GetCurrentAnimation() { return _CurrentAnimation; }
		int GetAnimationFrameIndex() const { return _AnimationFrameIndex; }

		void SetAnimationFrameIndex(std::size_t NewFrameIndex) { _AnimationFrameIndex = NewFrameIndex; }

		// VComponent's Functions
		void LoadComponent(const nlohmann::json& Descr) override;
		void SaveComponent(std::vector<std::uint8_t>& ByteArray) override;

	private:

		std::unique_ptr<Graphics::Spritesheet> _Spritesheet;
		std::unique_ptr<Graphics::Spritesheet::Animation> _CurrentAnimation;
		int _AnimationFrameIndex;
	};
}


