//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\VComponent.h"
#include "VComponent.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_VComponent_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("VComponent", "VulcanEngine::VComponent",sizeof(VulcanEngine::VComponent));
        c->Parent = &VulcanCore::ReflectionBase::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::VComponent), c); 
        return c; 
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

VULCAN_ENGINE_API VClass& VulcanEngine::VComponent::StaticClass() { 
    return *VC_Construct_VClass_VComponent(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::VComponent::GetClass() const { 
    return VComponent::StaticClass(); 
}; 

