#pragma once
#include "CoreAPI/Types.h"

enum EPropertyFlags : uint32 {
    PropertyFlags_None = 0,

    PropertyFlags_ZeroConstructor = 1 << 0, // Indicates that this property can be memset to zero to initialize (e.g., struct with no constructor, all basic types and arrays of such)
    PropertyFlags_IsPOD = 1 << 1, // Same as ZeroConstructor, but used for copying properties
};

enum EPropertyTypeFlags : uint32 {
    PropertyTypeFlags_None = 0,

    PropertyTypeFlags_Int8 = 1 << 0,
    PropertyTypeFlags_Int16 = 1 << 1,
    PropertyTypeFlags_Int = 1 << 2,
    PropertyTypeFlags_Int64 = 1 << 3,
    PropertyTypeFlags_Float = 1 << 4,
    PropertyTypeFlags_Double = 1 << 5,

    PropertyTypeFlags_UInt8 = 1 << 6,
    PropertyTypeFlags_UInt16 = 1 << 7,
    PropertyTypeFlags_UInt = 1 << 8,
    PropertyTypeFlags_UInt64 = 1 << 9,
    
};

enum ECastClassFlags : uint32 {
    CastClassFlags_None = 0,

    CastClassFlags_VField = 1 << 0,
    CastClassFlags_VProperty = 1 << 1,
    CastClassFlags_VNumericProperty = 1 << 2,
    
    CastClassFlags_VInt8Property = 1 << 3,
    CastClassFlags_VInt16Property = 1 << 4,
    CastClassFlags_VIntProperty = 1 << 5,
    CastClassFlags_VInt64Property = 1 << 6,
    CastClassFlags_VFloatProperty = 1 << 7,
    CastClassFlags_VDoubleProperty = 1 << 8,
    CastClassFlags_VUInt8Property = 1 << 9,
    CastClassFlags_VUInt16Property = 1 << 10,
    CastClassFlags_VUIntProperty = 1 << 11,
    CastClassFlags_VUInt64Property = 1 << 12,
};