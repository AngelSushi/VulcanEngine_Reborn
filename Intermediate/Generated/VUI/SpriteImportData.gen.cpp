//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <precomp.h>

#include "Requests\ImportRequestDatas\SpriteImportData.h"
#include "SpriteImportData.vht.h"

using namespace VulcanCore; 

struct VC_Construct_VStruct_SpriteImportData_Statics {
    static void RegisterProperties(VScriptStruct& s); 

    static VScriptStruct* Construct() { 
        auto* s = new VScriptStruct("SpriteImportData", "VUI::SpriteImportData", sizeof(VUI::SpriteImportData));
        s->Parent = &VUI::ImportData::StaticStruct(); 
        RegisterProperties(*s); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::SpriteImportData), s); 
        return s; 
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

VScriptStruct& VUI::SpriteImportData::StaticStruct() { 
    return *VC_Construct_VStruct_SpriteImportData(); 
}; 

void VC_Construct_VStruct_SpriteImportData_Statics::RegisterProperties(VScriptStruct& s) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_AssetName = {"InputText"}; 
    MetaMap meta_AssetName; 
    meta_AssetName["Category"] = std::string("General"); 
    s.AddProperty(std::make_unique<VProperty<VUI::SpriteImportData,std::string>>("AssetName", &VUI::SpriteImportData::AssetName, attrs_AssetName, meta_AssetName)); 

    std::vector<std::string> attrs_Folders = {}; 
    MetaMap meta_Folders; 
    meta_Folders["Category"] = std::string("General"); 
    s.AddProperty(std::make_unique<VProperty<VUI::SpriteImportData,VulcanEngine::TVector<std::string>>>("Folders", &VUI::SpriteImportData::Folders, attrs_Folders, meta_Folders)); 

}; 

