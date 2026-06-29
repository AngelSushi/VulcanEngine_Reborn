//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Types\Assets\SpriteAsset.h"
#include "SpriteAsset.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_SpriteAsset_Statics {

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_SpriteAsset() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_SpriteAsset_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_SpriteAsset { 
    VC_CompiledInDefer_SpriteAsset() { 
        (void)VC_Construct_VClass_SpriteAsset(); 
    } 
}; 

static VC_CompiledInDefer_SpriteAsset VC_CompiledInDefer_SpriteAsset_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_SpriteAsset(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return SpriteAsset::StaticClass(); 
}; 

