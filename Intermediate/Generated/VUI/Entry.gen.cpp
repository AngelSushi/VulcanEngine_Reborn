//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\Entry.h"
#include "Entry.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_Entry_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("Entry", "VUI::Entry",sizeof(VUI::Entry));
        c->Parent = &VulcanCore::ReflectionBase::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::Entry), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_Entry() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_Entry_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_Entry { 
    VC_CompiledInDefer_Entry() { 
        (void)VC_Construct_VClass_Entry(); 
    } 
}; 

static VC_CompiledInDefer_Entry VC_CompiledInDefer_Entry_Obj; 

 VClass& VUI::Entry::StaticClass() { 
    return *VC_Construct_VClass_Entry(); 
}; 

 VClass& VUI::Entry::GetClass() const { 
    return Entry::StaticClass(); 
}; 

