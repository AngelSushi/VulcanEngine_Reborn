//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\Entry.h"
#include "Entry.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_Entry_Statics {

    static VClass* Construct() { 
        return nullptr; 
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

 VClass& ::StaticClass() { 
    return *VC_Construct_VClass_Entry(); 
}; 

 VClass& ::GetClass() const { 
    return Entry::StaticClass(); 
}; 

