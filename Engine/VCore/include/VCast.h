#pragma once

#include "Reflection/VObject.h"

namespace VulcanCore {
    template<typename T>
    T* Cast(ReflectionBase* Obj) {
        if (!Obj) {
            return nullptr; 
        }

        if (Obj->GetClass().IsA<T>()) {
            return static_cast<T*>(Obj);
        }

        return nullptr;
    }

    template<typename T>
    T* Cast(const ReflectionBase* Obj) {
        if (!Obj) {
            return nullptr; 
        }

        if (Obj->GetClass().IsA<T>()) {
            return static_cast<T*>(const_cast<T*>(Obj));
        }

        return nullptr;
    }

    template<typename T>
     T* Cast(const std::any& Value) {
        if (!Value.has_value()) {
            return nullptr;
        }

        if (Value.type() == typeid(T*)) {
            try {
                return std::any_cast<T*>(Value);
            }
            catch (...) {
                return nullptr;
            }
        }

        return nullptr;
     }
}