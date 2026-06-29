//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Vulcan\World.h"
#include "World.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_World_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
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

VULCAN_ENGINE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_World(); 
}; 

VULCAN_ENGINE_API VClass& ::GetClass() const { 
    return World::StaticClass(); 
}; 

void VC_Construct_VClass_World_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::World&>>("GetWorld", &::GetWorld)); 
   c.AddFunction(std::make_unique<VStaticFunction<VulcanEngine::World&>>("Instance", &::Instance)); 
   c.AddFunction(std::make_unique<VFunction<,void>>("BuildTree", &::BuildTree)); 
}; 

