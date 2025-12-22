//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "ThemeAsset.h"
#include "ThemeAsset.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_ThemeAsset_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("ThemeAsset", "VUI::ThemeAsset",sizeof(VUI::ThemeAsset));
        c->Parent = &VulcanEngine::VAsset::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::ThemeAsset), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_ThemeAsset() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_ThemeAsset_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_ThemeAsset { 
    VC_CompiledInDefer_ThemeAsset() { 
        (void)VC_Construct_VClass_ThemeAsset(); 
    } 
}; 

static VC_CompiledInDefer_ThemeAsset VC_CompiledInDefer_ThemeAsset_Obj; 

 VClass& VUI::ThemeAsset::StaticClass() { 
    return *VC_Construct_VClass_ThemeAsset(); 
}; 

 VClass& VUI::ThemeAsset::GetClass() const { 
    return ThemeAsset::StaticClass(); 
}; 

