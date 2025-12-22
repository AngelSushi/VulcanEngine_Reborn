#pragma once

#include <string>
#include <unordered_map>

#include "Enums.h"
#include "CoreAPI/Types.h"

namespace VulcanCore {
    class VField;
    
    class VFieldClass {
    public:
        // InName should be const, but not possible with unordered_map key
        VFieldClass(char* InName, uint64 InId,uint64 CastFlags, VFieldClass* InSupperClass, VField* (*InConstructFn)(VField* InOwner,const char* InName));
        VField* ConstructDefault();

        
        static std::unordered_map<char*,VFieldClass*>& GetNameToFieldMap();

        uint64 GetId() const {
            return Id;
        }

        uint64 GetCastFlags() const {
            return CastFlags;
        }

        bool IsChildOf(const VFieldClass* InClass) const {
            return InClass->GetId() ? (CastFlags & InClass->GetCastFlags()) != 0 : IsChildOfInternal(InClass);
        }
        
        VField* Construct(VField* InOwner,const char* InName) const {
            return ConstructFn(InOwner,InName);
        }

        VFieldClass* GetSuperClass() const {
            return SuperClass;
        }

        VField* GetDefault() {
            if (!Default) {
                Default = ConstructDefault();
            }

            return Default;
        }

    private:
        bool IsChildOfInternal(const VFieldClass* InClass) const {
            const VFieldClass* current = this;

            while (current) {
                if (current == InClass) {
                    return true;
                }

                current = current->GetSuperClass();
            }

            return false;
        }

        std::string Name;
        uint64 Id = 0;
        uint64 CastFlags = 0;
        // Class Flags for future ?

        VFieldClass* SuperClass = nullptr;
        VField* (*ConstructFn)(VField* InOwner,const char* InName) = nullptr;
        
        VField* Default = nullptr;
    };

    // For all reflected elements 
    class VField { 
    public:

        typedef VField Super;

        VField(VFieldClass* InClass);
        VField(VField* InOwner, const char* InName);
        
        virtual ~VField() = default;


        virtual size_t GetFieldSize()  const {
            return sizeof(VField);
        }

        static constexpr uint64 StaticClassCastFlagsInternal() {
            return uint64(CastClassFlags_VField);
        }

        static constexpr uint64 StaticClassCastFlags() {
            return uint64(CastClassFlags_VField);
        }

        VFieldClass* GetClass() const {
            return Class;
        }

        uint64 GetCastFlags() const {
            return GetClass()->GetCastFlags();
        }

        static VField* Construct(const VField* InOwner,const char* InName);
        static VField* Construct(const char* InTypeName, const VField* InOwner,const char* InName);
        
        bool IsA(const VFieldClass* InClass) const {
            return GetClass()->IsChildOf(InClass);
        }

        template<typename T>
        bool IsA() const {
            if constexpr (T::StaticClassCastFlagsInternal() != 0) {
                return (GetCastFlags() & T::StaticClassCastFlagsInternal()) != 0;
            } else {
                return GetClass()->IsChildOf(T::StaticClass());
            }
        }
        

        const std::string& GetName() const { return Name; }

        
    private:
        std::string Name;
        VFieldClass* Class;
        VField* Owner;

        VField* Next; // Next field in linked list

        std::unordered_map<std::string,std::string> MetaDataMap;
    };

}
