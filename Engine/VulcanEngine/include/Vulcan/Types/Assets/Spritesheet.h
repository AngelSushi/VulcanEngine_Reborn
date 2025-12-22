#pragma once
#include <Export.h>

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <Vector2.h>


namespace VulcanEngine::Graphics {

	class VULCAN_ENGINE_API Spritesheet {
		
	public:
		struct Animation {
		public:
			VMath::Vector2i Size;
			VMath::Vector2i Start;
			unsigned int FrameCount;
			float FrameDuration;

			Animation() = default;

			Animation(const Animation& Animation) {
				Size = Animation.Size;
				Start = Animation.Start;
				FrameCount = Animation.FrameCount;
				FrameDuration = Animation.FrameDuration;
			}

			Animation(const std::unique_ptr<Animation>& Animation) {
				Size = Animation->Size;
				Start = Animation->Start;
				FrameCount = Animation->FrameCount;
				FrameDuration = Animation->FrameDuration;
			}
		};

		void AddAnimation(std::string Name, unsigned int FrameCount, float FrameDuration, VMath::Vector2i Start, VMath::Vector2i Size);

		const Animation& GetAnimation(std::size_t AnimIndex) const;
		std::optional<std::size_t> GetAnimationByName(std::string& AnimName) const;

		std::size_t GetAnimationCount() const;
	
	private:
		std::unordered_map<std::string, std::size_t> _AnimationByName;
		std::vector<Animation> _Animations;
	};
}


