#pragma once
namespace VulcanCore {
    class VClass;
    
    class ReflectionBase {
        
    public:
        
        virtual ~ReflectionBase() = default;
        virtual VClass& GetClass() const;

       // static VClass& StaticClass();
    };
}


