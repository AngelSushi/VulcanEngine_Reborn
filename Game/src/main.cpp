 //#include "providers/IAssetIconProvider.h"
#include <Game.h>
#include <iostream>
#include <IRegistry.h>
#include <Actions/AssetsAction.h>
#include <Actions/FolderAction.h>
//#include <Systems/EditorSystem.h>
#include <Systems/RenderSystem.h>
#include <Types/Assets/AssetsManager.h>

#include "Systems/EditorSystem.h"
#include "Systems/FontSystem.h"


 //#include "Systems/FontSystem.h"

 namespace VGame {

 	// Maybe destroy this class, game seems nothing in the current architecture of the engine
	class VGame : public Game {
		
		void LoadRegistries() override {
			/*VulcanEngine::ThemeRegistry.Load([]() {
				return VulcanEngine::AssetsManager::Instance().LoadAll<VUI::ThemeAsset>(".vtheme");
			});
			
			VulcanEngine::TreeIconProviderRegistry.Register(std::make_unique<VUI::IAssetIconProvider>());
			*/
			EngineActionRegistry.Register(IEngineAction::Create<AssetsAction>());
			EngineActionRegistry.Register(IEngineAction::Create<FolderAction>());
		}
		
		void SetupSystems() override {
			
			RenderSystem::SetConfig({
				.Title = "VulcanEngine",
				//.Size = { 2560, 1325}
				.Size = { 1920, 1080},
				.Flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
			});
			
			AddSystem<RenderSystem>();
			AddSystem<FontSystem>();
			AddSystem<EditorSystem>();
		}
	};
}

int main(int argc, char** argv) {
	VGame::VGame game;

	auto runResult = game.Run();

	return runResult == Game::RunResult::Success ? 0 : 1;
}
