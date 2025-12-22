#pragma once
#include <Export.h>
#include <functional>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include <string>

namespace VulcanEngine {
    enum VULCAN_ENGINE_API InputMouse {
        NO_MOUSE_INPUT = 0,
        LEFT_CLICK = 1,
        MIDDLE_CLICK = 2,
        RIGHT_CLICK = 3,
        X1 = 4,
        X2 = 5
    };

    class VULCAN_ENGINE_API InputManager {

    public:
        InputManager() = default;
        InputManager& operator=(const InputManager&) = delete;

        static InputManager& Instance() {
            static std::unique_ptr<InputManager> Instance(new InputManager);
            return *Instance; 
        }

        // Mettre constructeur et destructeur pour l'instance 

        void BindKeyPressed(SDL_Keycode Key, std::string ActionName);
        void BindMouseButton(InputMouse MouseIndex, std::string ActionName) ;

        void BindAction(const std::string ActionName, std::function<void(bool isActive)> Func);

        void RebindKey(SDL_Keycode Last, SDL_Keycode New);
        void RebindMouse(InputMouse LastMouseIndex, InputMouse NewMouseIndex);

        void HandleInputs(SDL_Event& Event); 

        bool IsActive(const std::string& ActionName);

        static SDL_Keycode _KeyPressed;
        static InputMouse _MousePressed;

    private:
        std::unordered_map<SDL_Keycode, std::string> InputBindings;
        std::unordered_map<InputMouse, std::string> MouseBindings;
        std::unordered_map<std::string, std::function<void(bool isActive)>> ActionBindings;

        std::unordered_map<std::string, unsigned int> _ActionCounters;

        void TriggerInputAction(SDL_Event& sdlEvent,bool isActive);
        void TriggerMouseAction(SDL_Event& sdlEvent,bool isActive);


    };
}
