#pragma once
#include <Reflection/VField.h>
#include <any>
#include <functional>
#include <string>
#include <typeinfo>
#include <fmt/core.h>

#include "VProperty.h"
#include "Reflection/VEnum.h"

namespace VulcanCore {

    class VEnumProperty : public VPropertyBase {
    public:
        
        void Draw() const override {
            
        }
        
        void* GetPtr(void* obj) const override {
           // return &(*static_cast<int*>(obj));
        }
        
        void SetRaw(void* obj, void* value) override;
        void* ConstructDefault() const override;
        void SetAsDefault(void* fieldPtr) const override;
        void Serialize(void* obj, std::ostream& out) const override;
        void Deserialize(void* obj, std::istream& in) const override;


        void SetEnum(VEnum* venum) {
            Enum = venum;
        }

        VEnum* GetEnum() const {
            return Enum;
        }
        
    private:
        VEnum* Enum;
    };
    
}
