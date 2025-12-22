#pragma once
#include <string>

#include "Model.h"

namespace EnumParser {
    std::vector<EnumInfo> ParseEnums(std::string& content);
    bool ParseEnum(EnumInfo& out,const std::string& content);
}
