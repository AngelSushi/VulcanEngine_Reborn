#pragma once

#ifdef VULCAN_ENGINE_BUILD
    #define VULCAN_ENGINE_API __declspec(dllexport)
#else
    #define VULCAN_ENGINE_API __declspec(dllimport)
#endif