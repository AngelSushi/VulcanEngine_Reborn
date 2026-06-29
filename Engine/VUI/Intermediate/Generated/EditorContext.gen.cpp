//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "EditorContext.h"
#include "EditorContext.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_EditorContext_Statics {
    static void RegisterFunctions(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
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

 VClass& ::StaticClass() { 
    return *VC_Construct_VClass_EditorContext(); 
}; 

 VClass& ::GetClass() const { 
    return EditorContext::StaticClass(); 
}; 

void VC_Construct_VClass_EditorContext_Statics::RegisterFunctions(VClass& c) { 
   c.AddFunction(std::make_unique<VStaticFunction<VUI::EditorContext&>>("Instance", &::Instance)); 
}; 

