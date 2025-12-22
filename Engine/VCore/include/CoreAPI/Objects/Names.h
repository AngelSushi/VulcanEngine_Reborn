#pragma once
#include <Windows.h>

#include "CoreAPI/Memory.h"
#include "CoreAPI/Types.h"
#include "CoreAPI/Templates/AlignTemplates.h"

struct NameEntry;
struct NameStringHeader;

/* 1 << n
 * Example : 4
 * 1 << 4
 * 0000 0001 << 4 - we move the bit to the left 4 times
 * 0001 0000 = 16 = 2^4
*/

static constexpr uint32 MaxNumOfBlocksInBits = 13;
static constexpr uint32 MaxNumOfBlocks = 1 << MaxNumOfBlocksInBits;

static constexpr uint32 MaxNumOfOffsetsInBits = 16;
static constexpr uint32 MaxNumOfOffsets = 1 << MaxNumOfOffsetsInBits;

struct NameEntryHandle {
    uint32 Block = 0;
    uint32 Offset = 0;

    NameEntryHandle(uint32 InBlock, uint32 InOffset)
        : Block(InBlock),
        Offset(InOffset) {}
    
};

struct NameEntryId {
    NameEntryId() : PackedValue(~0u) {}

    bool IsValid() {
        return PackedValue != ~0u;
    }

    
    static NameEntryId FromInteger(uint32 InPackedValue) {
        NameEntryId EntryId;
        EntryId.PackedValue = InPackedValue;
        return EntryId;
    } 

    static NameEntryId FromHandle(NameEntryHandle Handle) {
        NameEntryId EntryId;
        EntryId.PackedValue = (Handle.Block << MaxNumOfOffsetsInBits) | (Handle.Offset & (MaxNumOfOffsets - 1));
        return EntryId;
    }

    uint32 GetBlocks() const {
        return PackedValue >> MaxNumOfOffsetsInBits;
    }

    uint32 GetOffset() const {
        return PackedValue & (MaxNumOfOffsets - 1);
    }
    
private:
    uint32 PackedValue; // 32 bits to store block and offset
};

// How to a read a name as a string
struct NameEntryHeader {
    uint32 Hash;
    uint16 Len;
};


struct NameEntry {
    NameStringHeader Header;

    NameEntry();    

    // We disable copy and move , cause NameEntry is a memory pool allocated object so we don't want to copy or move it
    NameEntry(const NameEntry&) = delete;
    NameEntry(NameEntry&&) = delete;
    NameEntry& operator=(const NameEntry&) = delete;
    NameEntry& operator=(NameEntry&&) = delete;
};

class NameEntryAllocator {

public:
    NameEntryAllocator() {
        Blocks[0] = AllocMemForBlock();
    }
    
    ~NameEntryAllocator() {
        for (int32 i = CurrentBlock; i >= 0; --i) {
            Memory::Free(Blocks[i]);
        }
    }

    void Reserve(uint32 NumBlocks) {
        for (uint32 idx = NumBlocks - 1; idx > CurrentBlock && Blocks[idx] == nullptr; --idx) {
            Blocks[idx] = AllocMemForBlock();
        }
    }

    // Allocate BytesLen in the pool and return a handle to it
    NameEntryHandle Allocate(uint32 BytesLen) {

        // We are not sure that BytesLen is correctly aligned, so we align it
        BytesLen = Align(BytesLen,alignof(NameEntry));
    }

    
private:
    
    uint8* AllocMemForBlock() {
        return  (uint8*) Memory::Alloc(sizeof(NameEntry));
    }

    uint32 CurrentBlock = 0;
    uint32 CurrentBytesCursor = 0;
    uint8* Blocks[] = {};
};

class NamePool {
public:
    NamePool() = default;
    
    void Store();

    void Find();

private:
    
};

class Name {
    
};