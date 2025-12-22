//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\Entity.h"
#include "Entity.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_Entity_Statics {

    static VClass* Construct() { 
        auto* c = new VClass("Entity", "VulcanEngine::Entity",sizeof(VulcanEngine::Entity));
        c->Parent = &VulcanCore::VObject::StaticClass(); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::Entity), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_Entity() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_Entity_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_Entity { 
    VC_CompiledInDefer_Entity() { 
        (void)VC_Construct_VClass_Entity(); 
    } 
}; 

static VC_CompiledInDefer_Entity VC_CompiledInDefer_Entity_Obj; 

VULCAN_ENGINE_API VClass& VulcanEngine::Entity::StaticClass() { 
    return *VC_Construct_VClass_Entity(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::Entity::GetClass() const { 
    return Entity::StaticClass(); 
}; 

