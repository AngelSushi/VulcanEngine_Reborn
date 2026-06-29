#pragma once
#include <CoreAPI/precomp.h>

namespace VulcanCore {
    class VClass;
    
    class VCORE_API ReflectionBase {
        
    public:
        
        virtual ~ReflectionBase() = default;
        virtual VClass& GetClass() const;

       // static VClass& StaticClass();
    };
}


