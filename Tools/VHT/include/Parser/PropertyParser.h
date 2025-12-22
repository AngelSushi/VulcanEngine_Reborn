#pragma once
#include <string>
#include <vector>

#include "Model.h"

namespace PropertyParser {
    void ParseAllProperties(ClassInfo& Out, std::string& Content);
    void ParseAllProperties(StructInfo& Out, std::string& Content);
    
    void ParseProperty(ClassInfo& Out, std::string& Content);
    void ParseProperty(StructInfo& Out, std::string& Content);
}
