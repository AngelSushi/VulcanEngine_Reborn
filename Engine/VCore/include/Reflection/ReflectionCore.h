#pragma once
#include <string>
#include <typeindex>
#include <unordered_map>

#include "VField.h"


namespace VulcanCore {

    using Hash = uint32;
    
    // Stock all the static instances of VField (e.g., VScriptStruct, VProperty, ...)
    class ReflectionCore {

    public:
        static ReflectionCore& Instance() {
            static ReflectionCore instance;
            return instance;
        }

        void RegisterType(Hash hash,VField* Field) {
            ByName[Field->GetName()] = Field;
        }

        VField* Find(Hash hash) {
            auto it = ByType.find(hash);
            return it != ByType.end() ? it->second : nullptr;
        }

        VField* Find(const std::string& FieldName) {
            auto it = ByName.find(FieldName);
            return it != ByName.end() ? it->second : nullptr;
        }

    private:
        std::unordered_map<std::string,VField*> ByName;
    };

}
