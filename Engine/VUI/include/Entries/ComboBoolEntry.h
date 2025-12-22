#pragma once
#include "ComboEntry.h"
#include <ComboBoolEntry.vht.h>


namespace VUI {
    
    VCLASS()
    class ComboBoolEntry : public ComboEntry {
        VCLASS_BODY()
        
    public:
        ComboBoolEntry(std::string InName, bool* InIsEnabled) : ComboEntry(std::move(InName)), IsEnabled(InIsEnabled) {}
        
        VPROPERTY()
        bool* IsEnabled;
    };
}
