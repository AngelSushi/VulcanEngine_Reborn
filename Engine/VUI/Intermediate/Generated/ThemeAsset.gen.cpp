//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "ThemeAsset.h"
#include "ThemeAsset.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_ThemeAsset_Statics {

    static VClass* Construct() { 
        return nullptr; 
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

 VClass& ::StaticClass() { 
    return *VC_Construct_VClass_ThemeAsset(); 
}; 

 VClass& ::GetClass() const { 
    return ThemeAsset::StaticClass(); 
}; 

