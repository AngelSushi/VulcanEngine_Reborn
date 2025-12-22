//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "LogSystem.h"
#include "LogCategory.vht.h"

#include <Reflection/VFieldRegistry.h>
#include <Reflection/Function/VStaticFunction.h>
#include <unordered_map>
#include <variant>

using namespace VulcanCore; 

// Begin Enum LogLevel
struct VC_Construct_VEnum_LogLevel_Statics { 
    static VEnum* Construct() { 
        auto* e = new VEnum("LogLevel"); 
        e->AddEntry("Info", static_cast<int>(VulcanEngine::LogLevel::Info)); 
        e->AddEntry("Debug", static_cast<int>(VulcanEngine::LogLevel::Debug)); 
        e->AddEntry("Warning", static_cast<int>(VulcanEngine::LogLevel::Warning)); 
        e->AddEntry("Error", static_cast<int>(VulcanEngine::LogLevel::Error)); 

        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::LogLevel), e); 
        return e; 
    } 
}; 

VEnum* VC_Construct_VEnum_LogLevel() { 
    static VEnum* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VEnum_LogLevel_Statics::Construct(); 
    } 
    return Singleton; 
} 

struct VC_CompiledInDeferEnum_LogLevel { 
    VC_CompiledInDeferEnum_LogLevel() { 
        (void)VC_Construct_VEnum_LogLevel(); 
    } 
}; 

static VC_CompiledInDeferEnum_LogLevel VC_CompiledInDeferEnum_LogLevel_Obj; 

// End Enum LogLevel

struct VC_Construct_VClass_LogCategory_Statics {
    static void RegisterProperties(VClass& c); 

    static VClass* Construct() { 
        auto* c = new VClass("LogCategory", "VulcanEngine::LogCategory",sizeof(VulcanEngine::LogCategory));
        c->Parent = &VulcanCore::ReflectionBase::StaticClass(); 
        RegisterProperties(*c); 
        VFieldRegistry::Instance().RegisterType(typeid(VulcanEngine::LogCategory), c); 
        return c; 
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

 VClass& VulcanEngine::LogCategory::StaticClass() { 
    return *VC_Construct_VClass_LogCategory(); 
}; 

 VClass& VulcanEngine::LogCategory::GetClass() const { 
    return LogCategory::StaticClass(); 
}; 

void VC_Construct_VClass_LogCategory_Statics::RegisterProperties(VClass& c) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_Name = {}; 
    MetaMap meta_Name; 
    c.AddProperty(std::make_unique<VProperty<VulcanEngine::LogCategory,std::string>>("Name", &VulcanEngine::LogCategory::Name, attrs_Name, meta_Name)); 

    std::vector<std::string> attrs_Enabled = {"UI_Combo"}; 
    MetaMap meta_Enabled; 
    c.AddProperty(std::make_unique<VProperty<VulcanEngine::LogCategory,bool>>("Enabled", &VulcanEngine::LogCategory::Enabled, attrs_Enabled, meta_Enabled)); 

}; 

