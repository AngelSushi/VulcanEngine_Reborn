//AUTO GENERATED. EDIT AT YOUR OWN RISK.
#include <precomp.h>

#include "Requests\ImportRequestDatas\ImportData.h"
#include "ImportData.vht.h"

using namespace VulcanCore; 

struct VC_Construct_VStruct_ImportData_Statics {
    static void RegisterProperties(VScriptStruct& s); 

    static VScriptStruct* Construct() { 
        auto* s = new VScriptStruct("ImportData", "VUI::ImportData", sizeof(VUI::ImportData));
        RegisterProperties(*s); 
        VFieldRegistry::Instance().RegisterType(typeid(VUI::ImportData), s); 
        return s; 
    } 
}; 

VScriptStruct* VC_Construct_VStruct_ImportData() { 
    static VScriptStruct* Singleton = nullptr; 
    if(!Singleton) { 
        Singleton = VC_Construct_VStruct_ImportData_Statics::Construct(); 
    } 
    return Singleton; 
}

struct VC_CompiledInDefer_VStruct_ImportData { 
    VC_CompiledInDefer_VStruct_ImportData() { 
        (void)VC_Construct_VStruct_ImportData(); 
    } 
}; 

static VC_CompiledInDefer_VStruct_ImportData VC_CompiledInDefer_ImportData_Obj; 

VScriptStruct& VUI::ImportData::StaticStruct() { 
    return *VC_Construct_VStruct_ImportData(); 
}; 

void VC_Construct_VStruct_ImportData_Statics::RegisterProperties(VScriptStruct& s) { 
    using MetaValue = std::variant<std::string, std::vector<std::string>>; 
    using MetaMap = std::unordered_map<std::string, MetaValue>; 

    std::vector<std::string> attrs_AssetName = {"InputText"}; 
    MetaMap meta_AssetName; 
    meta_AssetName["Category"] = std::string("General"); 
    s.AddProperty(std::make_unique<VProperty<VUI::ImportData,std::string>>("AssetName", &VUI::ImportData::AssetName, attrs_AssetName, meta_AssetName)); 

    std::vector<std::string> attrs_Folders = {}; 
    MetaMap meta_Folders; 
    meta_Folders["Category"] = std::string("General"); 
    s.AddProperty(std::make_unique<VProperty<VUI::ImportData,VulcanEngine::TVector<std::string>>>("Folders", &VUI::ImportData::Folders, attrs_Folders, meta_Folders)); 

}; 

