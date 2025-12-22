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
    class VStringProperty : public VPropertyBase {
        
    public:
        using PropMember = std::string C::*;
        PropMember Member;

        VStringProperty(const std::string& prop_name,PropMember member, std::vector<std::string> prop_attrs = {}, MetaMap prop_datas) : VPropertyBase(std::move(prop_name), typeid(std::string), std::move(prop_attrs), std::move(prop_datas)), Member(member) {}

        void Draw() const override {
            
        }
        
        void* GetPtr(void* obj) const override {
            return &(static_cast<C*>(obj)->*Member);
        }
        
        void SetRaw(void* obj, void* value) override {
            C* instance = static_cast<C*>(obj);
            instance->*Member = *static_cast<std::string*>(value);
        }
        
        void* ConstructDefault() const override {
            return new std::string();
        }
        
        void SetAsDefault(void* fieldPtr) const override {
            *static_cast<std::string*>(fieldPtr) = std::string();
        }

        void Serialize(void* obj, std::ostream& out) const override {
            
        }
        void Deserialize(void* obj, std::istream& in) const override {
            
        }
    };
    
}
