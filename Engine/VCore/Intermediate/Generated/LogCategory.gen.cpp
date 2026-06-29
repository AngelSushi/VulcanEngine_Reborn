//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "LogSystem.h"
#include "LogCategory.vht.h"

#include <Reflection/ReflectionCore.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

struct VC_Construct_VClass_LogCategory_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        return nullptr; 
    } 
}; 

VClass* VC_Construct_VClass_LogCategory() { 
    static VClass* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VClass_LogCategory_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_LogCategory { 
    VC_CompiledInDefer_LogCategory() { 
        (void)VC_Construct_VClass_LogCategory(); 
    } 
}; 

static VC_CompiledInDefer_LogCategory VC_CompiledInDefer_LogCategory_Obj; 

VCORE_API VClass& ::StaticClass() { 
    return *VC_Construct_VClass_LogCategory(); 
}; 

VCORE_API VClass& ::GetClass() const { 
    return LogCategory::StaticClass(); 
}; 

void VC_Construct_VClass_LogCategory_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_Name = {}; 
    MetaMap meta_Name; 
    std::vector<std::string> attrs_Enabled = {"UI_Combo"}; 
    MetaMap meta_Enabled; 
}; 

