#pragma once
#include <Reflection/VField.h>
#include <any>
#include <functional>
#include <string>
#include <typeinfo>
#include <fmt/core.h>

#include "VProperty.h"

namespace VulcanCore {

    template<typename C>
    class VFloatProperty : public VPropertyBase {
    public:
        using PropMember = float C::*;
        PropMember Member;

        
        void Draw() const override {
            
        }
        
        void* GetPtr(void* obj) const override {
            return &(static_cast<C*>(obj)->*Member);
        }
        
        void SetRaw(void* obj, void* value) override {
            C* instance = static_cast<C*>(obj);
            instance->*Member = *static_cast<float*>(value);
        }
        
        void* ConstructDefault() const override {
            return new float(0.0f);
        }
        
        void SetAsDefault(void* fieldPtr) const override {
            *static_cast<float*>(fieldPtr) = 0.0f;
        }
        
        void Serialize(void* obj, std::ostream& out) const override {}
        void Deserialize(void* obj, std::istream& in) const override {}
    };
    
}
