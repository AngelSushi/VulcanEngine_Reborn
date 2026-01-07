#pragma once
#include <string>
#include <typeindex>
#include <unordered_map>

#include "VField.h"


namespace VulcanCore {
    
    // Stock all the static instances of VField (e.g., VScriptStruct, VProperty, ...)
    class ReflectionCore {

    public:
        static ReflectionCore& Instance() {
            static ReflectionCore instance;
            return instance;
        }

        void RegisterType(Name FName,VField* Field) {
            ByName[Field->GetName()] = Field;
        }

        VField* Find(Name FName) {
            auto it = ByName.find(FName);
            return it != ByName.end() ? it->second : nullptr;
        }

    private:
        std::unordered_map<Name,VField*> ByName;
    };

}
