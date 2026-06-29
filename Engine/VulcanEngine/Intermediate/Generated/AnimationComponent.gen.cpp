//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Components\AnimationComponent.h"
#include "AnimationComponent.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_AnimationComponent_Statics {

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_AnimationComponent() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_AnimationComponent_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_AnimationComponent { 
    VC_CompiledInDefer_AnimationComponent() { 
        (void)VC_Construct_VClass_AnimationComponent(); 
    } 
}; 

static VC_CompiledInDefer_AnimationComponent VC_CompiledInDefer_AnimationComponent_Obj; 

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_AnimationComponent(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return AnimationComponent::StaticClass(); 
}; 

