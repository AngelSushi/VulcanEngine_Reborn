#pragma once
#include <any>
#include <complex.h>
#include <string>
#include <vector>

#include <Reflection/VField.h>

namespace VulcanCore  {
    class ReflectionBase;

    enum class EFunctionFlags : uint32_t {
        EFunctionFlags_None = 0,

        // Nature of function
        EFunctionFlags_Member = 1 << 0,
        EFunctionFlags_Static = 1 << 1,
        EFunctionFlags_Const = 1 << 2,

        // Return type
        EFunctionFlags_ReturnsCopy = 1 << 3,
        EFunctionFlags_ReturnsRef = 1 << 4,
        EFunctionFlags_ReturnsPointer = 1 << 5,
        EFunctionFlags_ReturnsConst = 1 << 6,

        // Parameter passing
        EFunctionFlags_ParamsByValue = 1 << 7,
        EFunctionFlags_ParamsByRef = 1 << 8,
        EFunctionFlags_ParamsByPointer = 1 << 9,
        EFunctionFlags_ParamsConst = 1 << 10,
        
        // High-level API 
        EFunctionFlags_ScriptCallable = 1 << 11,
        EFunctionFlags_EditorCallable = 1 << 12,
        
    };

    inline EFunctionFlags operator|(EFunctionFlags a, EFunctionFlags b) {
        return static_cast<EFunctionFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    inline EFunctionFlags& operator|=(EFunctionFlags& a, EFunctionFlags b) {
        a = a | b;
        return a;
    }

    inline bool HasFlag(EFunctionFlags a, EFunctionFlags b) {
        return (static_cast<uint32_t>(a) & static_cast<uint32_t>(b)) != 0;
    }

    struct VFunctionParamInfo {
        const std::type_info* Type;
        std::string Name;
        bool IsRef;
        bool IsPointer;
        bool IsConst;
    };

    template<typename T>
    struct ParamTrait {
        using RawNoPtrRef = std::remove_cv_t<std::remove_reference_t<std::remove_pointer_t<T>>>;
        using Raw = std::remove_const_t<std::remove_reference_t<T>>;
        static constexpr bool IsRef = std::is_reference_v<T>;
        static constexpr bool IsConst = std::is_const_v<std::remove_reference_t<T>>;
        static constexpr bool IsPointer = std::is_pointer_v<T>;
    };

    template<typename T>
    struct IsConstMemberFunction : std::false_type {};

    template<typename C,typename R,typename... Args>
    struct IsConstMemberFunction<R(C::*)(Args...) const> : std::true_type {};
    
    struct FunctionRefValue {
        void* Ptr = nullptr;
        const std::type_info* Type = nullptr;
        bool IsConst = false;
    };
}
