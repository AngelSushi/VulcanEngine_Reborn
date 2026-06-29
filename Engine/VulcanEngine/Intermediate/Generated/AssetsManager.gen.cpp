//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Types\Assets\AssetsManager.h"
#include "AssetsManager.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_AssetsManager_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_AssetsManager() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_AssetsManager_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_AssetsManager { 
    VC_CompiledInDefer_AssetsManager() { 
        (void)VC_Construct_VClass_AssetsManager(); 
    } 
}; 

static VC_CompiledInDefer_AssetsManager VC_CompiledInDefer_AssetsManager_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_AssetsManager(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return AssetsManager::StaticClass(); 
}; 

void VC_Construct_VClass_AssetsManager_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::AssetsManager&>>("Instance", &::Instance)); 
}; 

