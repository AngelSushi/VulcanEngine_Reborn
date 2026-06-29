#include <LogSystem.h>

#include <CoreAPI/IRegistry.h>

namespace VulcanCore {

    DEFINE_LOG_CATEGORY(Other);

    VulcanEngine::IRegistry<LogCategory> LogCategoryRegistry;
}


