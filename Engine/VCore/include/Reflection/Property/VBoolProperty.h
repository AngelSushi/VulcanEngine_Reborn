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
    class VBoolProperty : public VPropertyBase {
    public:
        using PropMember = bool C::*;
        PropMember Member;

        VBoolProperty(const std::string& name,PropMember member,const std::vector<std::string>& attrs, const MetaMap& datas)
            : VPropertyBase(std::move(name), typeid(bool), std::move(attrs), std::move(datas)),Member(member) {
        }

        void Draw() const override {
            
        }
        

        void* GetPtr(void* obj) const override {
            return &(static_cast<C*>(obj)->*Member);
        }
        
        void SetRaw(void* obj, void* value) override {
            C* instance = static_cast<C*>(obj);
            instance->*Member = *static_cast<bool*>(value);
        }

        void* ConstructDefault() const override {
            return new bool(false);
        }

        void SetAsDefault(void* fieldPtr) const override {
            *static_cast<bool*>(fieldPtr) = false;
        }

        void Serialize(void* obj, std::ostream& out) const override {}

        void Deserialize(void* obj, std::istream& in) const override {}
    };
    
}
