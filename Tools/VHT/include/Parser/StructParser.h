#pragma once
#include <string>
#include <vector>

#include "Model.h"

namespace StructParser {
    
    std::vector<StructInfo> ParseStructs(std::string& content);
    bool ParseStruct(StructInfo& Out, std::string& Content);
}
