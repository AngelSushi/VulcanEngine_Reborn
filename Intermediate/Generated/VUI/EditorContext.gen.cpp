//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "EditorContext.h"
#include "EditorContext.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_EditorContext_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("EditorContext", "VUI::EditorContext",sizeof(VUI::EditorContext));
        c->Parent = &VulcanCore::ReflectionBase::StaticClass(); 
        RegisterFunctions(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::EditorContext), c); 
        return c; 
    } 
}; 

VClass* VC_Construct_VClass_EditorContext() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_EditorContext_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_EditorContext { 
    VC_CompiledInDefer_EditorContext() { 
        (void)VC_Construct_VClass_EditorContext(); 
    } 
}; 

static VC_CompiledInDefer_EditorContext VC_CompiledInDefer_EditorContext_Obj; 

 VClass& VUI::EditorContext::StaticClass() { 
    return *VC_Construct_VClass_EditorContext(); 
}; 

 VClass& VUI::EditorContext::GetClass() const { 
    return EditorContext::StaticClass(); 
}; 

void VC_Construct_VClass_EditorContext_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VUI::EditorContext&>>("Instance", &VUI::EditorContext::Instance)); 
}; 

