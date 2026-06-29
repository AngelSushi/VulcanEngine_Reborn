//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\Transform.h"
#include "Transform.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_Transform_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_Transform() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_Transform_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_Transform { 
    VC_CompiledInDefer_Transform() { 
        (void)VC_Construct_VClass_Transform(); 
    } 
}; 

static VC_CompiledInDefer_Transform VC_CompiledInDefer_Transform_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_Transform(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return Transform::StaticClass(); 
}; 

void VC_Construct_VClass_Transform_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_Position = {}; 
    MetaMap meta_Position; 
    std::vector<std::string> attrs_Rotation = {}; 
    MetaMap meta_Rotation; 
    std::vector<std::string> attrs_Scale = {}; 
    MetaMap meta_Scale; 
}; 

