#pragma once
#include <functional>
#include <unordered_set>


namespace VulcanCore {
    class VObject;

    class VObjectContext {
        friend class ObjectManager;
    public:
        void RegisterObject(VObject* Obj) {
            Objects.insert(Obj);
        }

        void UnregisterObject(VObject* Obj) {
            Objects.erase(Obj);
        }

        VObject* FindIf(std::function<bool(VObject*)> Pred) const {
            for (auto obj : Objects) {
                if (Pred(obj)) {
                    return obj;
                }
            }

            return nullptr;
        }

        const std::unordered_set<VObject*>& GetObjects() const {
            return Objects;
        }

    private:
        std::unordered_set<VObject*> Objects;
    };
}
