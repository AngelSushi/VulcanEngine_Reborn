//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <CoreAPI/precomp.h>

#include "Requests\ImportRequestDatas\SpriteImportData.h"
#include "SpriteImportData.vht.h"

using namespace VulcanCore; 

struct VC_Construct_VStruct_SpriteImportData_Statics {
    static void RegisterProperties(VScriptStruct& s); 

    static VScriptStruct* Construct() { 
        return nullptr; 
    } 
}; 

VScriptStruct* VC_Construct_VStruct_SpriteImportData() { 
    static VScriptStruct* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VStruct_SpriteImportData_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_VStruct_SpriteImportData { 
    VC_CompiledInDefer_VStruct_SpriteImportData() { 
        (void)VC_Construct_VStruct_SpriteImportData(); 
    } 
}; 

static VC_CompiledInDefer_VStruct_SpriteImportData VC_CompiledInDefer_SpriteImportData_Obj; 

VScriptStruct& ::StaticStruct() { 
    return *VC_Construct_VStruct_SpriteImportData(); 
}; 

void VC_Construct_VStruct_SpriteImportData_Statics::RegisterProperties(VScriptStruct& s) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_AssetName = {"InputText"}; 
    MetaMap meta_AssetName; 
    meta_AssetName["Category"] = std::string("General"); 
    std::vector<std::string> attrs_Folders = {}; 
    MetaMap meta_Folders; 
    meta_Folders["Category"] = std::string("General"); 
}; 

