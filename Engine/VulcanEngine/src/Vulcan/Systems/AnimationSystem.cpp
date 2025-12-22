#include <Systems/AnimationSystem.h>
#include <fmt/core.h>

namespace VulcanEngine {

	void AnimationSystem::InitSystem() {
		VSystem::InitSystem();
	}

	void AnimationSystem::StartSystem() {
		VSystem::StartSystem();
	}

	void AnimationSystem::Iterate(float DeltaTime) {
		VSystem::Iterate(DeltaTime);

		fmt::println("Tick Anim System");

/*		for (Entity* Entity : EntityRegistry::Instance().GetEntitiesWithComponent<AnimationComponent>()) {
			AnimationComponent* Animation = (AnimationComponent*)Entity->GetComponent<AnimationComponent>();

			if (Animation->GetCurrentAnimation() != nullptr) {
 				std::unique_ptr<Graphics::Spritesheet::Animation>& Anim = Animation->GetCurrentAnimation();

				if (Animation->GetAnimationFrameIndex() <= Anim->FrameCount) {
					_AnimTimer += DeltaTime;

					if (_AnimTimer >= Anim->FrameDuration) {
						_AnimTimer = 0.F;
						RenderComponent* Render = (RenderComponent*) Entity->GetComponent<RenderComponent>(); 

						fmt::println("Index {0}", Animation->GetAnimationFrameIndex());
						//Render->GetSprite()->SetRect({	32 * Animation->GetAnimationFrameIndex(),0,32,32}); // A Modifier selon la taille de la texture (pas forc�ment du 32x32)
						
						Animation->SetAnimationFrameIndex(Animation->GetAnimationFrameIndex() + 1);

						if (Animation->GetAnimationFrameIndex() >= Anim->FrameCount) {
							Animation->SetAnimationFrameIndex(0);
						}
					}	
				}
			}
		}
		*/
	}
}
