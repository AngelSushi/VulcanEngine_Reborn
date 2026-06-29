#pragma once

#ifdef VULCAN_ENGINE_BUILD
    #define VULCAN_ENGINE_API __declspec(dllexport)
#else
    #define VULCAN_ENGINE_API __declspec(dllimport)
#endif

#ifdef VUI_BUILD
    #define VUI_API __declspec(dllexport)
#else
    #define VUI_API __declspec(dllimport)
#endif

#ifdef VCORE_BUILD
    #define VCORE_API __declspec(dllexport)
#else
    #define VCORE_API __declspec(dllimport)
#endif