//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\CameraComponent.h"
#include "CameraComponent.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_CameraComponent_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("CameraComponent", "VulcanEngine::CameraComponent",sizeof(VulcanEngine::CameraComponent));
        c->Parent = &VulcanEngine::VComponent::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::CameraComponent), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_CameraComponent() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_CameraComponent_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_CameraComponent { 
    VC_CompiledInDefer_CameraComponent() { 
        (void)VC_Construct_VClass_CameraComponent(); 
    } 
}; 

static VC_CompiledInDefer_CameraComponent VC_CompiledInDefer_CameraComponent_Obj; 

VULCAN_ENGINE_API VClass& VulcanEngine::CameraComponent::StaticClass() { 
    return *VC_Construct_VClass_CameraComponent(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::CameraComponent::GetClass() const { 
    return CameraComponent::StaticClass(); 
}; 

