//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Entries\ComboEntry.h"
#include "ComboEntry.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_ComboEntry_Statics {
    static void RegisterProperties(VClass& c); 
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("ComboEntry", "VUI::ComboEntry",sizeof(VUI::ComboEntry));
        c->Parent = &VUI::Entry::StaticClass(); 
        RegisterProperties(*c); 
        RegisterFunctions(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::ComboEntry), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_ComboEntry() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_ComboEntry_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_ComboEntry { 
    VC_CompiledInDefer_ComboEntry() { 
        (void)VC_Construct_VClass_ComboEntry(); 
    } 
}; 

static VC_CompiledInDefer_ComboEntry VC_CompiledInDefer_ComboEntry_Obj; 

 VClass& VUI::ComboEntry::StaticClass() { 
    return *VC_Construct_VClass_ComboEntry(); 
}; 

 VClass& VUI::ComboEntry::GetClass() const { 
    return ComboEntry::StaticClass(); 
}; 

void VC_Construct_VClass_ComboEntry_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_EntryName = {}; 
    MetaMap meta_EntryName; 
    meta_EntryName["type"] = std::vector<std::string>{"Selectable","Text"}; 
    meta_EntryName["type_func"] = std::string("ResolvePropertyWidgetType"); 
    c.AddProperty(std::make_unique<VProperty<VUI::ComboEntry,std::string>>("EntryName", &VUI::ComboEntry::EntryName, attrs_EntryName, meta_EntryName)); 

}; 

void VC_Construct_VClass_ComboEntry_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VFunction<VUI::ComboEntry,std::string,ReflectionBase*,VulcanCore::VPropertyBase*,const std::vector<std::string>&>>("ResolvePropertyWidgetType", &VUI::ComboEntry::ResolvePropertyWidgetType)); 
}; 

