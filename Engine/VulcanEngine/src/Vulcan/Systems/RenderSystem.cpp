#include <Systems/RenderSystem.h>
#include <fmt/core.h>
#include <Entity.h>
#include <CoreAPI/VRenderer.h>
#include "CoreAPI/VTexture.h"

#include <imgui.h>

#include <CoreAPI/VCore.h>

#include <EventTrigger.h>
#include <Game.h>

namespace VulcanEngine {

	RenderSystem::RenderSystem(){
		
		VWindow& Window = VulcanCore::VCore::GetInstance().CreateWindow({
			.Title = Config.Title,
			.Position = Config.Position.has_value() ? Config.Position.value() : VMath::Vector2i{SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED},
			.Size = Config.Size,
			.Flags = Config.Flags
		});

		VulcanCore::VCore::GetInstance().CreateRenderer({
			.Window = Window, // Copy ???
			.Renderer = -1,
			.Flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		});

		Game::GetFrameBeginEvent().Register(this,&RenderSystem::OnPreFrame,LOW);
		Game::GetFrameEndEvent().Register(this,&RenderSystem::OnPostFrame,LOW);
	}

	void RenderSystem::Shutdown() {}

	void RenderSystem::InitSystem() {
		VSystem::InitSystem();
	}

	void RenderSystem::StartSystem() {
		VSystem::StartSystem();

	}

	void RenderSystem::OnPreFrame() {
		for (auto& [windowName,renderer] : VulcanCore::VCore::GetInstance().GetAllRenderers()) {
			SDL_RenderClear(renderer->GetRenderer());
		}
		
		//SDL_RenderClear(Renderer->GetRenderer());
	}

	void RenderSystem::Iterate(float DeltaTime) {
		VSystem::Iterate(DeltaTime);
		
		//SDL_Renderer* MainRenderer = VCore::Instance().GetMainRenderer()->GetRenderer();

//		SDL_SetRenderTarget(MainRenderer,VEditor::Instance().GetSceneTexture().get()->GetTexture());

	//	SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
		//SDL_RenderClear(MainRenderer);

	/*	MatrixFloat CameraMatrix = MatrixFloat::Identity();

		Entity* Camera = EntityRegistry::Instance().GetEntityCamera();

		VEditor& Editor = VEditor::Instance();
		
		if (Camera) {
			CameraMatrix = Camera->GetTransform()->GetTransformMatrix();
			CameraMatrix = CameraMatrix.GetInverse();
		}

		for (Entity* Entity : EntityRegistry::Instance().GetEntitiesWithComponent<RenderComponent>()) {
			RenderComponent* Render = (RenderComponent*) Entity->GetComponent<RenderComponent>();
			
			MatrixFloat WorldMatrix = Entity->GetTransform()->GetTransformMatrix();
			MatrixFloat WorldViewMatrix = CameraMatrix * WorldMatrix;

			Render->GetRenderable()->Draw(*Entity->GetRenderer(),WorldViewMatrix,Render->GetColor());
		}

		//SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
		//SDL_SetRenderTarget(MainRenderer, nullptr);
		//SDL_RenderClear(MainRenderer);
*/
		
	}

	void RenderSystem::OnPostFrame() {
		for (auto& [windowName,renderer] : VulcanCore::VCore::GetInstance().GetAllRenderers()) {
			SDL_RenderPresent(renderer->GetRenderer());
		}
		
		//SDL_RenderPresent(Renderer->GetRenderer());
	}
}
