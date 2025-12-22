#include <Components/AnimationComponent.h>
#include <fmt/core.h>
namespace VulcanEngine {

	AnimationComponent::AnimationComponent(std::unique_ptr<Graphics::Spritesheet>&& Spritesheet) :
	_Spritesheet(std::move(Spritesheet)), _CurrentAnimation(nullptr), _AnimationFrameIndex(0) {
	}

	AnimationComponent::AnimationComponent(AnimationComponent&& MoveSpriteSheet) noexcept
	: _Spritesheet(std::move(MoveSpriteSheet._Spritesheet)), _CurrentAnimation(std::move(MoveSpriteSheet._CurrentAnimation)), _AnimationFrameIndex(MoveSpriteSheet._AnimationFrameIndex) {
	
	}

	AnimationComponent& AnimationComponent::operator=(const AnimationComponent& CopySpritesheet) {
		_Spritesheet = std::make_unique<Graphics::Spritesheet>(*CopySpritesheet._Spritesheet);
		_CurrentAnimation = std::make_unique<Graphics::Spritesheet::Animation>(CopySpritesheet._CurrentAnimation);
		_AnimationFrameIndex = CopySpritesheet._AnimationFrameIndex;
		return *this;
	}

	AnimationComponent& AnimationComponent::operator=(AnimationComponent&& MoveSpritesheet) noexcept {
		_Spritesheet = std::move(MoveSpritesheet._Spritesheet);
		_CurrentAnimation = std::move(MoveSpritesheet._CurrentAnimation);
		_AnimationFrameIndex = MoveSpritesheet._AnimationFrameIndex;
		return *this;
	}

	void AnimationComponent::Play(std::string AnimName) {
		std::unique_ptr<Graphics::Spritesheet::Animation> PlayAnimation = std::make_unique<Graphics::Spritesheet::Animation>(_Spritesheet->GetAnimation(_Spritesheet->GetAnimationByName(AnimName).value()));

		if (PlayAnimation->FrameCount > 0) {
			_CurrentAnimation = std::make_unique<Graphics::Spritesheet::Animation>(*PlayAnimation);
		}
	}

	void AnimationComponent::Stop() {
		_AnimationFrameIndex = 0;
		_CurrentAnimation = nullptr;
	}

	void AnimationComponent::LoadComponent(const nlohmann::json& Descr) {}

	void AnimationComponent::SaveComponent(std::vector<std::uint8_t>& ByteArray) {}


}