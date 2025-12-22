#pragma once
#include <string>

#include "Model.h"

namespace CodeGenCpp {

    void GenerateClass(const ClassInfo& class_info,std::vector<EnumInfo> enums, const std::string& output_path);
    void GenerateStruct(const StructInfo& struct_info,std::vector<EnumInfo> enums,const std::string& output_path);
    void GenerateEnumPart(const EnumInfo& enum_info, std::ostringstream& out);
}
