#include <gsl/assert>
#include <Reflection/VField.h>

namespace VulcanCore {
    VFieldClass::VFieldClass(Name InName, uint64 InId, uint64 InCastFlags, VFieldClass* InSupperClass,VField*(* InConstructFn)(const VField* InOwner,Name InName))
        : FName(InName),
        Id(InId),
        CastFlags(InCastFlags),
        SuperClass(InSupperClass),
        ConstructFn(InConstructFn) {

        GetNameToFieldMap()[InName] = this;
    }

    VField* VFieldClass::ConstructDefault() {
        return nullptr;
    }

    std::unordered_map<Name, VFieldClass*>& VFieldClass::GetNameToFieldMap() {
        static std::unordered_map<Name,VFieldClass*> NameToFieldMap;
        return NameToFieldMap;
    }

    VField::VField(VFieldClass* InClass)
        : Class(InClass),
        Owner(nullptr),
        Next(nullptr) {
    }

    VField::VField(const VField* InOwner,Name InFName) 
        : Owner(InOwner),
        FName(InFName),
        Class(nullptr),
        Next(nullptr) {

    }

    VField* VField::Construct(const VField* InOwner,Name InName) {
        return nullptr;
    }

    VField* VField::Construct(Name InTypeName, const VField* InOwner,Name InName) {
        auto it = VFieldClass::GetNameToFieldMap().find(InTypeName);
        Expects(it != VFieldClass::GetNameToFieldMap().end());

        VField* Instance = (it->second)->Construct(InOwner,InName);
        return Instance;
    }
}

    
