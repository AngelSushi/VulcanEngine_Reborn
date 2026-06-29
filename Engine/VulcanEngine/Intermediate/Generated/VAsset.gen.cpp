//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Types\Assets\VAsset.h"
#include "VAsset.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_VAsset_Statics {

    static VClass* Construct() { 
        return nullptr; 
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

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_VAsset(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return VAsset::StaticClass(); 
}; 

