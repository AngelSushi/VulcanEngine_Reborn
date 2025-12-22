//AUTO GENERATED. EDIT AT YOUR OWN RISK.

#pragma once
#include <typeindex>
#include <Reflection/VClass.h>
#include <Reflection/VEnum.h>

// Begin Enum LogLevel
namespace VulcanEngine { enum class LogLevel; } 

struct VC_Construct_VEnum_LogLevel_Statics;
::VulcanCore::VEnum* VC_Construct_VEnum_LogLevel(); 

namespace VulcanCore { 
    template <> 
    inline VEnum& StaticEnum<VulcanEngine::LogLevel>() { 
        return *VC_Construct_VEnum_LogLevel(); 
    } 
} 
// End Enum LogLevel

namespace VulcanCore { class ObjectManager; } 

struct VC_Construct_VClass_LogCategory_Statics; 
::VulcanCore::VClass* VC_Construct_VClass_LogCategory(); 

#undef VCLASS_BODY()
#define VCLASS_BODY() \
friend class ::VulcanCore::ObjectManager; \
template<typename T,typename... Args> \
friend T* ::VulcanCore::NewObject(Args&&... args); \
friend struct VC_Construct_VClass_LogCategory_Statics;\
public: \
    static ::VulcanCore::VClass& StaticClass(); \
    virtual ::VulcanCore::VClass& GetClass() const override;
