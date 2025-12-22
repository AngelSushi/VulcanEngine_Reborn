#pragma once
#include <Reflection/VMacros.h>

#include <ImportData.vht.h>

namespace VUI {

    VSTRUCT()
    struct ImportData {
        VSTRUCT_BODY()
        
        VPROPERTY(Category=General,InputText)
        std::string AssetName;
        
        VPROPERTY(Category=General)
        VulcanEngine::TVector<std::string> Folders;
    };
}
