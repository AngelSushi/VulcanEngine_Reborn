#pragma once
#include <string>
#include <vector>

#include "Model.h"

namespace Parser {
    struct ParseResult {
        std::vector<ClassInfo> Classes;
        std::vector<StructInfo> Structs;
        std::vector<EnumInfo> Enums;
    };
    ParseResult Parse(const std::vector<std::pair<std::string,std::string>>& Files);
}
