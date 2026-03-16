#pragma once
#include <CoreAPI/precomp.h>

// Represent a value in the UI system, which can be a string, number, boolean, or color.
// Must be replace by property system later.

// std::get can failed in specific sdk's (maybe sdk like console?) so we may implements our own system after. 

using UIData = std::variant<std::string, float, bool,int>;

struct UIValue {
    UIData Value;

public:
    UIValue() = default;
    UIValue(const std::string& InValue) : Value(InValue) {}
    UIValue(std::string&& InValue) : Value(std::move(InValue)) {}
    UIValue(float InValue) : Value(InValue) {}
    UIValue(bool InValue) : Value(InValue) {}
    UIValue(int InValue) : Value(InValue) {}
    
    template<typename T>
    bool Is() const {
        return std::holds_alternative<T>(Value);
    }

    template<typename T>
    T Get() const {
        return std::get<T>(Value);
    }
};