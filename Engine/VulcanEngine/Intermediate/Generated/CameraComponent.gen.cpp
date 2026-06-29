//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\CameraComponent.h"
#include "CameraComponent.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_CameraComponent_Statics {

    static VClass* Construct() { 
        return nullptr; 
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

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_CameraComponent(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return CameraComponent::StaticClass(); 
}; 

