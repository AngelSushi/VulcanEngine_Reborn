//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\ResourceManager.h"
#include "ResourceManager.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_ResourceManager_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("ResourceManager", "VulcanEngine::Resources::ResourceManager",sizeof(VulcanEngine::Resources::ResourceManager));
        c->Parent = &VulcanCore::VObject::StaticClass(); 
        RegisterFunctions(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::Resources::ResourceManager), c); 
        return c; 
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

VULCAN_ENGINE_API VClass& VulcanEngine::Resources::ResourceManager::StaticClass() { 
    return *VC_Construct_VClass_ResourceManager(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::Resources::ResourceManager::GetClass() const { 
    return ResourceManager::StaticClass(); 
}; 

void VC_Construct_VClass_ResourceManager_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::Resources::ResourceManager&>>("Instance", &VulcanEngine::Resources::ResourceManager::Instance)); 
}; 

