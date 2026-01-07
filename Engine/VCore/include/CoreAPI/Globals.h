#pragma once
#include "Enums.h"
#include "Reflection/VClass.h"


namespace VCG {
    
#if WITH_METADATA
    struct MetaDataPairParam {
        const char* Key;
        const char* Value;
    };
#endif
    
    struct FunctionLinkInfo {
        const char* Name;    
    };

    struct PropertyBaseParams {
        char* Name;
        EPropertyTypeFlags PropertyType;
        EPropertyFlags PropertyFlags;
        uint16 ElementCount;
    };

    struct PropertyParamsWithOffset {
        char* Name;
        EPropertyTypeFlags PropertyType;
        EPropertyFlags PropertyFlags;
        uint16 ElementCount;
        uint16 Offset;
    };

    struct PropertyParamsWithoutOffset {
        char* Name;
        EPropertyTypeFlags PropertyType;
        EPropertyFlags PropertyFlags;
        uint16 ElementCount;
    };

    struct PropertyParamsGeneric {
        char* Name;
        EPropertyTypeFlags PropertyType;
        EPropertyFlags PropertyFlags;
        uint16 ElementCount;
        uint16 Offset;
        #if WITH_METADATA
                uint16 SizeMetaData;
                MetaDataPairParam* MetaData;
        #endif
    };

    typedef PropertyParamsGeneric Int8PropertyParams;
    typedef PropertyParamsGeneric Int16PropertyParams;
    typedef PropertyParamsGeneric IntPropertyParams;
    typedef PropertyParamsGeneric Int64PropertyParams;
    typedef PropertyParamsGeneric FloatPropertyParams;
    typedef PropertyParamsGeneric DoublePropertyParams;
    typedef PropertyParamsGeneric UInt8PropertyParams;
    typedef PropertyParamsGeneric UInt16PropertyParams;
    typedef PropertyParamsGeneric UIntPropertyParams;
    typedef PropertyParamsGeneric UInt64PropertyParams;
    
    struct ClassParams {
        VulcanCore::VClass* (*ClassRegisterFunc)();
        const char* ClassName;
        const PropertyBaseParams* const* PropertiesArray; // Array of pointers to properties
        FunctionLinkInfo* FunctionLinkInfo;
        uint32 NumFunctions;
        uint32 NumProperties;
        uint32 ClassFlags;
    };
    
    void ConstructClass(VulcanCore::VClass* OutClass, const ClassParams& Params);
}
