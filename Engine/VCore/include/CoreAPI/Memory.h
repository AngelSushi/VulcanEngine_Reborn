#pragma once

struct VMemory {

    static void* Alloc(size_t InSize) {
        return nullptr;
    }
    
    static void Free(void* InMem) {
        
    }

    
    // Can be made FORCEINLINE mais nécessite une autre macro que VMacros pour éviter les dépendances circulaires
    static void Memcpy(const void* Src, void* Dst, size_t InSize) {
        
    }
};
