//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\TreeEntry.h"
#include "TreeEntry.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_TreeEntry_Statics {

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_TreeEntry() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_TreeEntry_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_TreeEntry { 
    VC_CompiledInDefer_TreeEntry() { 
        (void)VC_Construct_VClass_TreeEntry(); 
    } 
}; 

static VC_CompiledInDefer_TreeEntry VC_CompiledInDefer_TreeEntry_Obj; 

 VClass& ::StaticClass() { 
    return *VC_Construct_VClass_TreeEntry(); 
}; 

 VClass& ::GetClass() const { 
    return TreeEntry::StaticClass(); 
}; 

