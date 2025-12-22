#pragma once
#include <string>
#include <vector>
#include <any>
#include <map>
#include <typeindex>

#include "Entry.h"
#include <HeaderEntry.vht.h>


namespace VUI {
    
    VCLASS()
    class HeaderEntry : public Entry {
        VCLASS_BODY()
        
    public:
        VPROPERTY()
        std::string HeaderName;

        VPROPERTY()
        std::map<VulcanCore::VPropertyBase*,ReflectionBase*> Properties;
    };
}
