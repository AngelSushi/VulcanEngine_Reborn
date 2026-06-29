//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\NameComponent.h"
#include "NameComponent.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_NameComponent_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_NameComponent() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_NameComponent_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_NameComponent { 
    VC_CompiledInDefer_NameComponent() { 
        (void)VC_Construct_VClass_NameComponent(); 
    } 
}; 

static VC_CompiledInDefer_NameComponent VC_CompiledInDefer_NameComponent_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_NameComponent(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return NameComponent::StaticClass(); 
}; 

void VC_Construct_VClass_NameComponent_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_Name = {"InputText"}; 
    MetaMap meta_Name; 
    meta_Name["onchange_func"] = std::string("World::BuildTree"); 
}; 

