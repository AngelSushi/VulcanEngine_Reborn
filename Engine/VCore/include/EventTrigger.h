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
    struct EventTrigger {

        struct Entry {
            EventPriority Priority;
            T Fn;
        };

        template<typename C>
        void Register(C* instance, void (C::*method)(), EventPriority priority = HIGH) {
            handler.push_back({priority, [instance, method]() { (instance->*method)(); }});
            std::sort(handler.begin(), handler.end(), [](const Entry& a, const Entry& b) {
                return a.Priority > b.Priority;
            });
        }

        template<typename... Args>
        void Trigger(bool InReverse = false,Args&...InArgs) {
            if (!InReverse) {
                for (auto it = handler.rbegin(); it != handler.rend(); ++it) {
                    it->Fn(InArgs...);
                }
            } else {
                for (auto& entry : handler) {
                    entry.Fn(InArgs...);
                }
            }
        }

    private:
        std::vector<Entry> handler;
    };

}
