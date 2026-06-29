//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\ResourceManager.h"
#include "ResourceManager.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_ResourceManager_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_ResourceManager() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_ResourceManager_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_ResourceManager { 
    VC_CompiledInDefer_ResourceManager() { 
        (void)VC_Construct_VClass_ResourceManager(); 
    } 
}; 

static VC_CompiledInDefer_ResourceManager VC_CompiledInDefer_ResourceManager_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_ResourceManager(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return ResourceManager::StaticClass(); 
}; 

void VC_Construct_VClass_ResourceManager_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::Resources::ResourceManager&>>("Instance", &::Instance)); 
}; 

