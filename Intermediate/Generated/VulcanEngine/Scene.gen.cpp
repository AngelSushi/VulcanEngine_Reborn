//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Types\Assets\Scene.h"
#include "Scene.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_Scene_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("Scene", "VulcanEngine::Scene",sizeof(VulcanEngine::Scene));
        c->Parent = &VulcanEngine::VAsset::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::Scene), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_Scene() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_Scene_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_Scene { 
    VC_CompiledInDefer_Scene() { 
        (void)VC_Construct_VClass_Scene(); 
    } 
}; 

static VC_CompiledInDefer_Scene VC_CompiledInDefer_Scene_Obj; 

VULCAN_ENGINE_API VClass& VulcanEngine::Scene::StaticClass() { 
    return *VC_Construct_VClass_Scene(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::Scene::GetClass() const { 
    return Scene::StaticClass(); 
}; 

