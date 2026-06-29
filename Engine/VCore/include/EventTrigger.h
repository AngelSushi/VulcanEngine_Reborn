#pragma once
#include <algorithm>
#include <vector>

namespace VulcanEngine {

    enum EventPriority {
        LOW = -100,
        MEDIUM = 0,
        HIGH = 100
    };
    
    template<typename T>
    class VCORE_API EventTrigger {

        struct Entry {
            EventPriority Priority;
            T Fn;
        };
    public:
        // Appear to no work with parameters in event function (Can't call Event.Register(this,FuncWithParams)
        template<typename C,typename... Args>
        void Register(C* instance, void (C::*method)(Args... args), EventPriority priority = HIGH) {
            handler.push_back({priority, [instance, method](Args... args) { (instance->*method)(args...); }});
            std::sort(handler.begin(), handler.end(), [](const Entry& a, const Entry& b) {
                return a.Priority > b.Priority;
            });
        }

        template<typename F>
        void RegisterLambda(F&& lambda, EventPriority priority = HIGH) {
            handler.push_back({priority, T(std::forward<F>(lambda))});
            std::sort(handler.begin(), handler.end(), [](const Entry& a, const Entry& b) {
                return a.Priority > b.Priority;
            });
        }

        // Not passing args by ref, can cause issues with non-copyable types. 
        template<typename... Args>
        void Trigger(Args...InArgs) {
            // HIGH -> LOW
            for (auto& entry : handler) {
                entry.Fn(InArgs...);
            }
        }

        template<typename... Args>
        void TriggerReverse(Args... InArgs) {
            // LOW -> HIGH
            for (auto it = handler.rbegin(); it != handler.rend(); ++it) {
                it->Fn(InArgs...);
            }
        }

    private:
        std::vector<Entry> handler;
    };

}
