//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\TreeEntry.h"
#include "TreeEntry.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_TreeEntry_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("TreeEntry", "VUI::TreeEntry",sizeof(VUI::TreeEntry));
        c->Parent = &VUI::Entry::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::TreeEntry), c); 
        return c; 
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

 VClass& VUI::TreeEntry::StaticClass() { 
    return *VC_Construct_VClass_TreeEntry(); 
}; 

 VClass& VUI::TreeEntry::GetClass() const { 
    return TreeEntry::StaticClass(); 
}; 

