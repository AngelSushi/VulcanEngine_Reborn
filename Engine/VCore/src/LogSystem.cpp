#include <LogSystem.h>

#include <CoreAPI/IRegistry.h>

namespace VulcanEngine {

    DEFINE_LOG_CATEGORY(Other);
    
    IRegistry<LogCategory> LogCategoryRegistry;
}


