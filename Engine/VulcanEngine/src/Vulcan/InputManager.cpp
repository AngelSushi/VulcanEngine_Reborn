#include <InputManager.h>
#include <SDL2/SDL.h>
#include <fmt/core.h>

namespace VulcanEngine {
    SDL_Keycode InputManager::_KeyPressed = 0;
    InputMouse InputManager::_MousePressed = InputMouse::NO_MOUSE_INPUT;

    void InputManager::BindKeyPressed(SDL_Keycode Key,std::string ActionName) {
        InputBindings[Key] = std::move(ActionName);
    }

    void InputManager::BindMouseButton(InputMouse MouseIndex, std::string ActionName) {
        InputMouse Mouse;

        switch (MouseIndex) {
            case SDL_BUTTON_RIGHT:
                Mouse = RIGHT_CLICK;
                break;
            case SDL_BUTTON_MIDDLE:
                Mouse = MIDDLE_CLICK;
                break;
            case SDL_BUTTON_LEFT:
                Mouse = LEFT_CLICK;
                break;
            case SDL_BUTTON_X1:
                Mouse = X1;
                break;
            case SDL_BUTTON_X2:
                Mouse = X2;
                break;
        }

        MouseBindings[Mouse] = std::move(ActionName);
    }

    void InputManager::BindAction(const std::string ActionName, std::function<void(bool isActive)> ActionFunc) {
        ActionBindings[ActionName] = std::move(ActionFunc);
        _ActionCounters[ActionName] = 0;
    }
    
    void InputManager::RebindKey(SDL_Keycode Last, SDL_Keycode New) {
        auto Target = InputBindings.find(Last);
        
        if (Target != InputBindings.end()) {
            std::string Action = std::move(Target->second);
            InputBindings.erase(Target);

            InputBindings[New] = std::move(Action);
        }
    }

    void InputManager::RebindMouse(InputMouse LastMouseIndex, InputMouse NewMouseIndex) {
        auto Target = MouseBindings.find(LastMouseIndex);

        if (Target != MouseBindings.end()) {
            std::string Action = std::move(Target->second);
            MouseBindings.erase(Target);

            MouseBindings[NewMouseIndex] = std::move(Action);
        }
    }

    void InputManager::HandleInputs(SDL_Event& Event) {
        switch (Event.type) {
            case SDL_KEYDOWN:
                if (Event.key.repeat != 0) {
                    break;
                }

                TriggerInputAction(Event, true);
                break;
            case SDL_KEYUP:
                TriggerInputAction(Event, false);
                break;
            case SDL_MOUSEBUTTONDOWN:
                TriggerMouseAction(Event, true);
                break;
            case SDL_MOUSEBUTTONUP:
                TriggerMouseAction(Event, false);
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                fmt::print("controller down");
                break;
        }
    }

    bool InputManager::IsActive(const std::string& ActionName) {
        auto it = _ActionCounters.find(ActionName);

        if (it == _ActionCounters.end()) {
            return false;
        }

        return it->second > 0;
    }

    void InputManager::TriggerInputAction(SDL_Event& sdlEvent,bool isActive) {
        if (InputBindings.find(sdlEvent.key.keysym.sym) != InputBindings.end()) {
            const std::string Action = InputBindings[sdlEvent.key.keysym.sym];

            if (ActionBindings.find(Action) != ActionBindings.end() && ActionBindings[Action]) {   
                if (isActive) {
                    if (_ActionCounters[Action]++ == 0) {
                        ActionBindings[Action](isActive);
                        _KeyPressed = sdlEvent.key.keysym.sym;
                    }
                }
                else {
                    if (--_ActionCounters[Action] == 0) {
                        ActionBindings[Action](isActive);
                        _KeyPressed = 0;
                    }
                }
            }
        }
    }

    void InputManager::TriggerMouseAction(SDL_Event& sdlEvent, bool isActive) {
        InputMouse Mouse;

        switch (sdlEvent.button.button) { // Changer le switch (voir github) 
        case SDL_BUTTON_RIGHT:
            Mouse = RIGHT_CLICK;
            break;
        case SDL_BUTTON_MIDDLE:
            Mouse =MIDDLE_CLICK;
            break;
        case SDL_BUTTON_LEFT:
            Mouse = LEFT_CLICK;
            break;
        case SDL_BUTTON_X1:
            Mouse =X1;
            break;
        case SDL_BUTTON_X2:
            Mouse = X2;
            break;
        }

        if (MouseBindings.find(Mouse) != MouseBindings.end()) {
            const std::string Action = MouseBindings[Mouse];

            if (ActionBindings.find(Action) != ActionBindings.end() && ActionBindings[Action]) {
                if (isActive) {
                    if (_ActionCounters[Action]++ == 0) {
                        ActionBindings[Action](isActive);
                        _MousePressed = Mouse;
                    }
                }
                else {
                    if (--_ActionCounters[Action] == 0) {
                        ActionBindings[Action](isActive);
                        _MousePressed = InputMouse::NO_MOUSE_INPUT;
                    }
                }
            }
        }
    }
}
