//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\World.h"
#include "World.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_World_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("World", "VulcanEngine::World",sizeof(VulcanEngine::World));
        c->Parent = &VulcanCore::VObject::StaticClass(); 
        RegisterFunctions(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::World), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_World() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_World_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_World { 
    VC_CompiledInDefer_World() { 
        (void)VC_Construct_VClass_World(); 
    } 
}; 

static VC_CompiledInDefer_World VC_CompiledInDefer_World_Obj; 

VULCAN_ENGINE_API VClass& VulcanEngine::World::StaticClass() { 
    return *VC_Construct_VClass_World(); 
}; 

VULCAN_ENGINE_API VClass& VulcanEngine::World::GetClass() const { 
    return World::StaticClass(); 
}; 

void VC_Construct_VClass_World_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::World&>>("GetWorld", &VulcanEngine::World::GetWorld)); 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::World&>>("Instance", &VulcanEngine::World::Instance)); 
   c.AddFunction(std::make_unique<VFunction<VulcanEngine::World,void>>("BuildTree", &VulcanEngine::World::BuildTree)); 
}; 

