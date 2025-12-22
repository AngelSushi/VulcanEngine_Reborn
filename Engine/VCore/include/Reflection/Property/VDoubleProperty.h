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
    class VDoubleProperty : public VPropertyBase {
    public:
        using PropMember = double C::*;
        PropMember Member;
        
        VDoubleProperty(const std::string& name,PropMember prop,onst std::vector<std::string>& attrs, const MetaMap& datas)
            : VPropertyBase(std::move(name), typeid(double), std::move(attrs), std::move(datas)), Member(prop) {}
        

        void Draw() const override {
            
        }
        
        void* GetPtr(void* obj) const override {
            return &(static_cast<C*>(obj)->*Member);
        }
        
        void SetRaw(void* obj, void* value) override {
            C* instance = static_cast<C*>(obj);
            instance->*Member = *static_cast<double*>(value);
        }
        
        void* ConstructDefault() const override {
            return new double(0);    
        }
        void SetAsDefault(void* fieldPtr) const override {
            *static_cast<double*>(fieldPtr) = 0;
        }
        
        void Serialize(void* obj, std::ostream& out) const override {}
        void Deserialize(void* obj, std::istream& in) const override {}
    };
    
}
