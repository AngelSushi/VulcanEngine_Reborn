//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Types\Assets\VAsset.h"
#include "VAsset.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_VAsset_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("VAsset", "VulcanEngine::VAsset",sizeof(VulcanEngine::VAsset));
        c->Parent = &VulcanCore::VObject::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::VAsset), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_VAsset() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_VAsset_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_VAsset { 
    VC_CompiledInDefer_VAsset() { 
        (void)VC_Construct_VClass_VAsset(); 
    } 
}; 

static VC_CompiledInDefer_VAsset VC_CompiledInDefer_VAsset_Obj; 

VULCAN_ENGINE_API VClass& VulcanEngine::VAsset::StaticClass() { 
    return *VC_Construct_VClass_VAsset(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::VAsset::GetClass() const { 
    return VAsset::StaticClass(); 
}; 

