//AUTO GENERATED. EDIT AT YOUR OWN RISK.

#pragma once
#include <typeindex>
#include <Reflection/VScriptStruct.h>
#include <Reflection/VEnum.h>

namespace VUI { struct SpriteImportData; } 

struct VC_Construct_VStruct_SpriteImportData_Statics; 
::VulcanCore::VScriptStruct* VC_Construct_VStruct_SpriteImportData(); 

namespace VulcanCore { 
    template<>
    inline VScriptStruct& StaticStruct<VUI::SpriteImportData>() { 
        return *VC_Construct_VStruct_SpriteImportData(); 
    }
}

#undef VSTRUCT_BODY()
#define VSTRUCT_BODY() \
public: \
    static ::VulcanCore::VScriptStruct& StaticStruct(); \
