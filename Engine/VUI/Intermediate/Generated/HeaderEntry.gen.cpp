//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\HeaderEntry.h"
#include "HeaderEntry.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_HeaderEntry_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_HeaderEntry() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_HeaderEntry_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_HeaderEntry { 
    VC_CompiledInDefer_HeaderEntry() { 
        (void)VC_Construct_VClass_HeaderEntry(); 
    } 
}; 

static VC_CompiledInDefer_HeaderEntry VC_CompiledInDefer_HeaderEntry_Obj; 

 VClass& ::StaticClass() { 
    return *VC_Construct_VClass_HeaderEntry(); 
}; 

 VClass& ::GetClass() const { 
    return HeaderEntry::StaticClass(); 
}; 

void VC_Construct_VClass_HeaderEntry_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_HeaderName = {}; 
    MetaMap meta_HeaderName; 
    std::vector<std::string> attrs_Properties = {}; 
    MetaMap meta_Properties; 
}; 

