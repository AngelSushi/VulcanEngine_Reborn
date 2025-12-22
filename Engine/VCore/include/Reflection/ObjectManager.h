#pragma once
#include "VObjectContext.h"
#include <fmt/core.h>

#include "TVector.h"


namespace VulcanCore {


    // Stock all the instance of objects in the engine
    
    class ObjectManager {
        
    public:
        static ObjectManager& Instance() {
            static ObjectManager instance;
            return instance;
        }

        void RegisterObject(VObject* Obj) {
            Objects.push_back(Obj);
        }

        void UnregisterObject(VObject* Obj) {
            Objects.remove(Obj);
        }
    

    private:
        VulcanEngine::TVector<VObject*> Objects;
    };

    template<typename T,typename... Args>
    inline T* NewObject(Args&&... args) {
        static_assert(std::is_base_of_v<VObject,T>,"T must be derived from VObject");

        fmt::print("Creating object of type: {}\n", typeid(T).name());

        T* obj = new T(std::forward<Args>(args)...);
        ObjectManager::Instance().RegisterObject(obj);
        return obj;
    }
}
