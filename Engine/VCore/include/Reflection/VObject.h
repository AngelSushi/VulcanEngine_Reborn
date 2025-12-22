#pragma once

#include "ReflectionBase.h"
#include "VMacros.h"

#include "ObjectManager.h"

namespace VulcanCore {
    class VInterface;
    class VClass;

    class VObject : public ReflectionBase {
        
    public:

        template<typename T>
        bool IsA() const;

        bool ImplementsInterface(const VInterface& Interface) const;
        
        virtual VClass& GetClass() const override = 0;

    protected:
        /*
         * Protected to prevent direct instantiation, use ObjectManager::NewObject<T>() instead
         * Don't redefine constructor in derived classes
         */
        VObject() = default;
        
        void* operator new(std::size_t Size) {
            return ::operator new(Size);
        }
        
        void* operator new[](std::size_t Size) {
            return ::operator  new[](Size);  
        }

        void operator delete(void* Ptr) {
            ::operator delete(Ptr);
        }

        void operator delete[](void* Ptr) {
            ::operator delete[](Ptr);
        }
    };
}
    #include "VClass.h"
    
    template <typename T>
    bool VulcanCore::VObject::IsA() const{
        return GetClass().IsA<T>();
    }

