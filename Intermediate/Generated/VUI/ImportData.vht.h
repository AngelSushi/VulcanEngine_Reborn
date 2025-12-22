//AUTO GENERATED. EDIT AT YOUR OWN RISK.

#pragma once
#include <typeindex>
#include <Reflection/VScriptStruct.h>
#include <Reflection/VEnum.h>

namespace VUI { struct ImportData; } 

struct VC_Construct_VStruct_ImportData_Statics; 
::VulcanCore::VScriptStruct* VC_Construct_VStruct_ImportData(); 

namespace VulcanCore { 
    template<>
    inline VScriptStruct& StaticStruct<VUI::ImportData>() { 
        return *VC_Construct_VStruct_ImportData(); 
    }
}

#undef VSTRUCT_BODY()
#define VSTRUCT_BODY() \
public: \
    static ::VulcanCore::VScriptStruct& StaticStruct(); \
