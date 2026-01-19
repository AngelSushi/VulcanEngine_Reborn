#pragma once
#include <CoreAPI/precomp.h>

using namespace std;
// Represent a value in the UI system, which can be a string, number, boolean, or color.
// Must be replace by property system later.

// std::get can failed in specific sdk's (maybe sdk like console?) so we may implements our own system after. 

using UIData = variant<std::string, double, bool,int>;

struct UIValue {
    UIData Value;

    template<typename T>
    UIValue(T&& InValue) : Value(forward<T>(InValue)) {}

    bool IsNull() {
        return holds_alternative<monostate>(Value);
    }
    
    template<typename T>
    bool GetValue() {
        return holds_alternative<T>(Value);
    }
};