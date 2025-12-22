#include "providers/IAssetIconProvider.h"
#include <Game.h>
#include <IRegistry.h>
#include <Actions/AssetsAction.h>
#include <Actions/FolderAction.h>
#include <Systems/EditorSystem.h>
#include <Systems/RenderSystem.h>
#include <Types/Assets/AssetsManager.h>

namespace VGame {
	class Game : public VulcanEngine::Game {
		
		void LoadRegistries() override {
			VulcanEngine::ThemeRegistry.Load([]() {
				return VulcanEngine::AssetsManager::Instance().LoadAll<VUI::ThemeAsset>(".vtheme");
			});
			
			VulcanEngine::TreeIconProviderRegistry.Register(std::make_unique<VUI::IAssetIconProvider>());
			
			VulcanEngine::EngineActionRegistry.Register(VulcanEngine::IEngineAction::Create<VulcanEngine::AssetsAction>());
			VulcanEngine::EngineActionRegistry.Register(VulcanEngine::IEngineAction::Create<VulcanEngine::FolderAction>());
		}
		
		void SetupSystems() override {

			VulcanEngine::RenderSystem::SetConfig({
				.Title = "VulcanEngine",
				//.Size = { 2560, 1325}
				.Size = { 1920, 1080}
			});
			
			AddSystem<VulcanEngine::RenderSystem>();
			AddSystem<VulcanEngine::EditorSystem>();
		}
	};
}

	int main(int argc, char** argv) {
	VGame::Game game;
	
	auto runResult = game.Run();

	return runResult == VulcanEngine::Game::RunResult::Success ? 0 : 1;
}
