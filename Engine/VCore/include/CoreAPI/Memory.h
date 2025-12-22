#pragma once
#include "Reflection/VMacros.h"

struct Memory {

    static void* Alloc(size_t InSize) {
        return nullptr;
    }
    
    static FORCEINLINE void Free(void* InMem) {
        
    }
    
};
