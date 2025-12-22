//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\HeaderEntry.h"
#include "HeaderEntry.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_HeaderEntry_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("HeaderEntry", "VUI::HeaderEntry",sizeof(VUI::HeaderEntry));
        c->Parent = &VUI::Entry::StaticClass(); 
        RegisterProperties(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::HeaderEntry), c); 
        return c; 
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

 VClass& VUI::HeaderEntry::StaticClass() { 
    return *VC_Construct_VClass_HeaderEntry(); 
}; 

 VClass& VUI::HeaderEntry::GetClass() const { 
    return HeaderEntry::StaticClass(); 
}; 

void VC_Construct_VClass_HeaderEntry_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_HeaderName = {}; 
    MetaMap meta_HeaderName; 
    c.AddProperty(std::make_unique<VProperty<VUI::HeaderEntry,std::string>>("HeaderName", &VUI::HeaderEntry::HeaderName, attrs_HeaderName, meta_HeaderName)); 

    std::vector<std::string> attrs_Properties = {}; 
    MetaMap meta_Properties; 
    c.AddProperty(std::make_unique<VProperty<VUI::HeaderEntry,std::map<VulcanCore::VPropertyBase*,ReflectionBase*>>>("Properties", &VUI::HeaderEntry::Properties, attrs_Properties, meta_Properties)); 

}; 

