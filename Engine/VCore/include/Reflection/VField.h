#pragma once

#include <string>
#include <unordered_map>

#include "Enums.h"
#include "CoreAPI/Types.h"
#include "CoreAPI/Objects/Names.h"

namespace VulcanCore {
    class VField;
    
    class VFieldClass {
    public:
        VFieldClass(Name InName, uint64 InId,uint64 CastFlags, VFieldClass* InSupperClass, VField* (*InConstructFn)(const VField* InOwner,Name InName));
        VField* ConstructDefault();

        
        static std::unordered_map<Name,VFieldClass*>& GetNameToFieldMap();

        uint64 GetId() const {
            return Id;
        }

        uint64 GetCastFlags() const {
            return CastFlags;
        }

        bool IsChildOf(const VFieldClass* InClass) const {
            return InClass->GetId() ? (CastFlags & InClass->GetCastFlags()) != 0 : IsChildOfInternal(InClass);
        }
        
        VField* Construct(const VField* InOwner,Name InName) const {
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

        Name FName;
        uint64 Id = 0;
        uint64 CastFlags = 0;
        // Class Flags for future ?

        VFieldClass* SuperClass = nullptr;
        VField* (*ConstructFn)(const VField* InOwner,Name InName) = nullptr;
        
        VField* Default = nullptr;
    };

    // For all reflected elements 
    class VField { 
    public:

        typedef VField Super;

        VField(VFieldClass* InClass);
        VField(const VField* InOwner, Name InFName);
        
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

        static VField* Construct(const VField* InOwner,Name InName);
        static VField* Construct(Name InTypeName, const VField* InOwner,Name InName);
        
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
        

        const Name& GetName() const { return FName; }

        static VFieldClass* StaticClass() {
            return nullptr;
        }
        
    private:
        Name FName;
        VFieldClass* Class;
        const VField* Owner;

        VField* Next; // Next field in linked list

        std::unordered_map<std::string,std::string> MetaDataMap;
    };

}
