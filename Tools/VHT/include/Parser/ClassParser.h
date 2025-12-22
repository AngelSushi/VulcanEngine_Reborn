#pragma once
#include <string>
#include <vector>

#include "Model.h"

namespace ClassParser {
    std::vector<ClassInfo> ParseClasses(std::string& content);
    bool ParseClass(ClassInfo& out, std::string& content);
}
