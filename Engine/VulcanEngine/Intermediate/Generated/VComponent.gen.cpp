//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\VComponent.h"
#include "VComponent.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_VComponent_Statics {

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_VComponent() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_VComponent_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_VComponent { 
    VC_CompiledInDefer_VComponent() { 
        (void)VC_Construct_VClass_VComponent(); 
    } 
}; 

static VC_CompiledInDefer_VComponent VC_CompiledInDefer_VComponent_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_VComponent(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return VComponent::StaticClass(); 
}; 

