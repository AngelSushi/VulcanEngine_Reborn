#pragma once
#include "Model.h"

namespace CodeGenHeader {
    
    void GenerateClass(const ClassInfo& classInfo,std::vector<EnumInfo> enums,const std::string& outputPath);
    void GenerateStruct(const StructInfo& structInfo,std::vector<EnumInfo> enums,const std::string& outputPath);
    void GenerateEnumPart(const EnumInfo& enumInfo, std::ostream& out);
}
