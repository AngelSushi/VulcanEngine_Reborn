#pragma once
#include <string>
#include <vector>

#include "Model.h"

namespace FunctionParser {
    void ParseAllFunctions(ClassInfo& Out, std::string& Content);
    
    void ParseFunction(ClassInfo& Out, std::string& Content);
}
