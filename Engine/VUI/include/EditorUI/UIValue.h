#pragma once
#include <CoreAPI/precomp.h>

// Represent a value in the UI system, which can be a string, number, boolean, or color.
// Must be replace by property system later.

// std::get can failed in specific sdk's (maybe sdk like console?) so we may implements our own system after. 

using UIData = std::variant<std::string, double, bool,int>;

struct UIValue {
    UIData Value;

    UIValue() {}
    
    template<typename T>
    UIValue(T&& InValue) : Value(std::forward<T>(InValue)) {}

   /* bool IsNull() { ADD monostate to variant if need IsNull
        return holds_alternative<monostate>(Value);
    }*/ 
    
    template<typename T>
    bool Is() {
        return std::holds_alternative<T>(Value);
    }
};