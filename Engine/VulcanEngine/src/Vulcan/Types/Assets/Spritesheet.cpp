#include <Types/Assets/SpriteSheet.h>

namespace VulcanEngine::Graphics {

	void Spritesheet::AddAnimation(std::string Name, unsigned int FrameCount, float FrameDuration, VMath::Vector2i Start, VMath::Vector2i Size) {
		_AnimationByName.emplace(std::move(Name), _Animations.size());

		Animation& NewAnimation = _Animations.emplace_back();

		NewAnimation.FrameCount = FrameCount;
		NewAnimation.FrameDuration = FrameDuration;
		NewAnimation.Start = Start;
		NewAnimation.Size = Size;
	}

	const Spritesheet::Animation& Spritesheet::GetAnimation(std::size_t AnimIndex) const {
		return _Animations[AnimIndex];
	}

	std::optional<std::size_t> Spritesheet::GetAnimationByName(std::string& AnimName) const {
		auto it = _AnimationByName.find(AnimName);

		if (it == _AnimationByName.end()) {
			return {};
		}

		return it->second;
	}

	std::size_t Spritesheet::GetAnimationCount() const {
		return _Animations.size();
	}

}