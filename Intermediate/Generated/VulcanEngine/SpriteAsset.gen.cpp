//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Types\Assets\SpriteAsset.h"
#include "SpriteAsset.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_SpriteAsset_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("SpriteAsset", "VulcanEngine::SpriteAsset",sizeof(VulcanEngine::SpriteAsset));
        c->Parent = &VulcanEngine::VAsset::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::SpriteAsset), c); 
        return c; 
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

VULCAN_ENGINE_API VClass& VulcanEngine::SpriteAsset::StaticClass() { 
    return *VC_Construct_VClass_SpriteAsset(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::SpriteAsset::GetClass() const { 
    return SpriteAsset::StaticClass(); 
}; 

