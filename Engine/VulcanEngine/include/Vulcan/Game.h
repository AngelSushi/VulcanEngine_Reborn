#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <fmt/color.h>

#include <Systems/VSystem.h>

#include "EventTrigger.h"



namespace VulcanEngine {
    class VULCAN_ENGINE_API Game {
    public:
        using FrameBeginEventType = std::function<void()>;
        using FrameEndEventType = std::function<void()>;
        using StartEventType = std::function<void()>;
        using QuitEventType = std::function<void()>;
        
        enum class RunResult {
            Success,
            Failure
          };
        

        Game() = default;
        Game(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;
        virtual ~Game() = default;

        RunResult Run();

        
        static EventTrigger<StartEventType>& GetStartEngineEvent() { return StartEngineEvent; }
        static EventTrigger<QuitEventType>& GetQuitEngineEvent() { return QuitEngineEvent; }
        static EventTrigger<FrameBeginEventType>& GetFrameBeginEvent() { return FrameBeginEvent; }
        static EventTrigger<FrameEndEventType>& GetFrameEndEvent() { return FrameEndEvent; }

    protected:
        virtual void LoadRegistries() = 0;
        virtual void SetupSystems() = 0;
        
        template<typename T>
        void AddSystem() {
            T& instance = T::Instance(); 
            systems.emplace_back(&instance); 
        }

    private:
        // gsl::not_null<ISystem*>
        std::vector<VSystem*> systems;

        
        static inline EventTrigger<StartEventType> StartEngineEvent;
        static inline EventTrigger<QuitEventType> QuitEngineEvent;
        static inline EventTrigger<FrameBeginEventType> FrameBeginEvent;
        static inline EventTrigger<FrameEndEventType> FrameEndEvent;


    };
}
