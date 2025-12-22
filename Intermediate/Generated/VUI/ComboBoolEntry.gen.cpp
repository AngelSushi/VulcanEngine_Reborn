//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\ComboBoolEntry.h"
#include "ComboBoolEntry.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_ComboBoolEntry_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("ComboBoolEntry", "VUI::ComboBoolEntry",sizeof(VUI::ComboBoolEntry));
        c->Parent = &VUI::ComboEntry::StaticClass(); 
        RegisterProperties(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::ComboBoolEntry), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_ComboBoolEntry() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_ComboBoolEntry_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_ComboBoolEntry { 
    VC_CompiledInDefer_ComboBoolEntry() { 
        (void)VC_Construct_VClass_ComboBoolEntry(); 
    } 
}; 

static VC_CompiledInDefer_ComboBoolEntry VC_CompiledInDefer_ComboBoolEntry_Obj; 

 VClass& VUI::ComboBoolEntry::StaticClass() { 
    return *VC_Construct_VClass_ComboBoolEntry(); 
}; 

 VClass& VUI::ComboBoolEntry::GetClass() const { 
    return ComboBoolEntry::StaticClass(); 
}; 

void VC_Construct_VClass_ComboBoolEntry_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_IsEnabled = {}; 
    MetaMap meta_IsEnabled; 
    c.AddProperty(std::make_unique<VProperty<VUI::ComboBoolEntry,bool*>>("IsEnabled", &VUI::ComboBoolEntry::IsEnabled, attrs_IsEnabled, meta_IsEnabled)); 

}; 

