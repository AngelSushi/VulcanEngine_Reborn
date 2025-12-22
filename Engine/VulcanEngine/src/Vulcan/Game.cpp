#include <Game.h>

#include <chrono>
#include <SDL_events.h>
#include <fmt/color.h>

#include <CoreAPI/VCore.h>
#include <CoreAPI/VWindow.h>

#include <World.h>
#include <Systems/EditorSystem.h>

namespace VulcanEngine {
    class UIAsset;

    Game::RunResult Game::Run() {
        std::unique_ptr<VulcanCore::VCore> Core = std::make_unique<VulcanCore::VCore>(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

        LoadRegistries();
        SetupSystems();
        
        auto& window = Core->GetWindow("VulcanEngine");
        auto& editorSystem = EditorSystem::Instance();

        
        auto lastTime = SDL_GetPerformanceCounter();

        for (unsigned int frame = 0; !window.IsClosed(); frame++) {
            if (frame == 0) {
                StartEngineEvent.Trigger();

                for (const auto& system : systems) {
                    system->StartSystem();
                }
            }
            
            auto now = SDL_GetPerformanceCounter();
            auto delta = (float)(now - lastTime) / SDL_GetPerformanceFrequency();

            lastTime = now;
            
            window.PollEvents(&editorSystem.GetGUIRenderer());

            FrameBeginEvent.Trigger();

            for (const auto& system : systems) {
                system->Iterate(delta);
            }

            FrameEndEvent.Trigger(true);
            
        }

        for (auto& system : systems) {
            system->Shutdown();
        }
        
    
        return RunResult::Success;
    }
}
