#pragma once

#include <string>
#include <CoreAPI/Memory.h>
#include <CoreAPI/Types.h>
#include <CoreAPI/Templates/AlignTemplates.h>
#include <gsl/assert>

struct NameEntry;
struct NameEntryHeader;
struct NameEntryHandle;
struct NameEntryId;
struct NameView;
struct NameHash;

class NameEntryAllocator;
class NamePool;

static constexpr uint16 MAX_NAME_LENGTH = 1024;

static constexpr uint32 MaxNumOfBlocksInBits   = 13;
static constexpr uint32 MaxNumOfBlocks         = 1 << MaxNumOfBlocksInBits;

static constexpr uint32 MaxNumOfOffsetsInBits  = 16;
static constexpr uint32 MaxNumOfOffsets        = 1 << MaxNumOfOffsetsInBits;

// Starting value for the hash. It was specially chosen because it's optimized for 64 bits and has historical validation. 
static constexpr uint64_t FNV1A64_OFFSET_BASIS = 14695981039346656037ull;

// Number by which we multiply after each byte. Choosen for same reason than starting value
static constexpr uint64_t FNV1A64_PRIME = 1099511628211ull;


// Only works for ASCII characters
static unsigned char ToLowerASCII(unsigned char Char) noexcept {
    return Char >= 'A' && Char <= 'Z' ? (unsigned char) (Char + ('a' - 'A')) : Char;
}

inline uint64 HashFNV1A(const void* data,size_t size) noexcept {
    const uint8* b = static_cast<const uint8*>(data);
    uint64 HASH = FNV1A64_OFFSET_BASIS;
 
    for (size_t i = 0; i < size; i++) {
        HASH ^= static_cast<uint64>(b[i]);
        HASH *= FNV1A64_PRIME;
    }
 
    return HASH;
}

inline uint64 HashFNV1A(const char* Str, uint32 Len) noexcept {
    uint64 HASH = FNV1A64_OFFSET_BASIS;
    Expects(Str && Len > 0);

    const unsigned char* Byte = reinterpret_cast<const unsigned char*>(Str);
    for (uint32 i = 0; i < Len; i++) {
        HASH ^= static_cast<uint64>(ToLowerASCII(Byte[i]));
        HASH *= FNV1A64_PRIME;
    }

    return HASH;
}

inline uint64 HashFNV1A(const char* Str) noexcept {
    uint64 HASH = FNV1A64_OFFSET_BASIS;
    Expects(Str);
    
    for (const unsigned char* Byte = reinterpret_cast<const unsigned char*>(Str); *Byte != '\0'; Byte++) {
        HASH ^= static_cast<uint64>(ToLowerASCII(*Byte));
        HASH *= FNV1A64_PRIME;
    }

    return HASH;
}

enum EFindState : uint8 {
    FindState_Add,
    FindState_Find
};

struct NameBuffer {

    NameBuffer() = default;

    void ReadFromEntry(const NameEntry& Entry) {
        
    }
};

struct NameView {
    int32 Len = 0;
    const char* Name = nullptr;

    bool IsValid() const {
        return Len > 0 && Name != nullptr;
    }

    bool Equals(NameView Other) {
        if (Len != Other.Len) {
            return false;
        }

        return std::memcmp(Name, Other.Name, Len) == 0;
    }

    bool operator==(NameView Other) {
        return Equals(Other);
    }
    
};

// Packed (Block | Offset)
struct NameEntryId {

    NameEntryId() : PackedValue(~0u) {}

    bool IsValid() const {
        return PackedValue != ~0u;
    }

    uint32 ToInteger() const {
        return PackedValue;
    }

    static NameEntryId FromInteger(uint32 InPackedValue) {
        NameEntryId Id;
        Id.PackedValue = InPackedValue;
        return Id;
    }

private:
    uint32 PackedValue;
};

struct NameEntryIds {
    NameEntryId Comparison;
    NameEntryId Display;
};

struct NameEntryHeader {
    uint16 Len : 10;
    uint16 ProbHash : 5;
};

struct NameHash {
    uint64 FullHash;
    uint32 MinHash;
    uint16 Len;

    static constexpr uint32 HashMask = (1 << 5) - 1;
    
    NameHash(const char* Str)
        : NameHash(Str,0) {};
    
    NameHash(const char* Str,uint32 Len)
        : NameHash(GenerateHash(Str, Len),Len) {}
    
    NameHash(NameEntryId StringPart)
        : NameHash(GenerateHash(StringPart),0) {}
    
    NameHash(uint64 InHash,uint16 InLen)
        : FullHash(InHash),
        Len(InLen) {
        MinHash = static_cast<uint32>(InHash) & HashMask;
    }

    uint64 GenerateHash(const char* Str, uint32 Len) {
        return HashFNV1A(Str,Len);
    }

    uint64 GenerateHash(const char* Str) {
        return HashFNV1A(Str);
    }

    uint64 GenerateHash(NameEntryId id) {
        return HashFNV1A(&id,sizeof(NameEntryId));
    }

    FORCEINLINE bool CompareFast(NameEntryHeader Header) {
        return Header.Len != 0 && Header.Len == Len && Header.ProbHash == MinHash;
    }

};


// Unpacked representation
struct NameEntryHandle {

    uint32 Block  = 0;
    uint32 Offset = 0;

    NameEntryHandle() = default;

    NameEntryHandle(uint32 InBlock, uint32 InOffset)
        : Block(InBlock), Offset(InOffset) {}

    NameEntryHandle(NameEntryId Id)
        : Block(Id.ToInteger() >> MaxNumOfOffsetsInBits),
        Offset(Id.ToInteger() & (MaxNumOfOffsets - 1)) {

    }

    operator NameEntryId() const {
        return NameEntryId::FromInteger((Block << MaxNumOfOffsetsInBits) | Offset);
    }
};


struct NameEntry {

    NameEntryId CompareEntry;
    NameEntryHeader Header;
    char* Name = nullptr;

private:
    NameEntry() = default;

    NameEntry(const NameEntry&)            = delete;
    NameEntry(NameEntry&&)                 = delete;
    NameEntry& operator=(const NameEntry&) = delete;
    NameEntry& operator=(NameEntry&&)      = delete;

public:

    static constexpr uint32 GetOffset() {
        return offsetof(NameEntry, Name);
    }
    
    void GetNameStr(char* Out) const {
        VMemory::Memcpy(Name,Out,Header.Len);
    }

    void AppendNameToString(std::string& Out) const {
        Expects(Header.Len != 0 && Name != nullptr);

        char Name[MAX_NAME_LENGTH];
        GetNameStr(Name);
        Out.append(Name,Header.Len);    
    }
    
    int32 GetNameLength() const {
        return Header.Len;
    }

    void StoreName(const char* InName, uint32 InLen) {
        VMemory::Memcpy(InName, Name, InLen);
    }
};

class NameEntryAllocator {

public:
    NameEntryAllocator() {
        Blocks[0] = AllocMemForBlock();
    }

    ~NameEntryAllocator() {
        for (uint32 i = 0; i <= CurrentBlock; ++i) {
            VMemory::Free(Blocks[i]);
        }
    }

    void Reserve(uint32 NumBlocks) {
        Expects(NumBlocks <= MaxNumOfBlocks);

        for (uint32 i = CurrentBlock + 1; i < NumBlocks; ++i) {
            if (Blocks[i] == nullptr) {
                Blocks[i] = AllocMemForBlock();
            }
        }
    }

    NameEntryHandle Allocate(uint32 BytesLen) {
        BytesLen = Align(BytesLen, alignof(NameEntry));
        Expects(BytesLen <= MaxNumOfOffsets * alignof(NameEntry));

        if (CurrentBytesCursor + BytesLen > MaxNumOfOffsets * alignof(NameEntry)) {
            AllocateNewBlock();
        }

        uint32 ByteOffset = CurrentBytesCursor;
        CurrentBytesCursor += BytesLen;

        uint32 OffsetIndex = ByteOffset / alignof(NameEntry); // Warning calcul douteux ???
        Expects(OffsetIndex < MaxNumOfOffsets);

        return NameEntryHandle(CurrentBlock, OffsetIndex);
    }

    NameEntryHandle Create(NameView View,NameEntryId ComparisonId) {
        NameEntryHandle Handle = Allocate(NameEntry::GetOffset() + View.Len);
        NameEntry& Entry = Resolve(Handle);

        Entry.CompareEntry = ComparisonId.IsValid() ? ComparisonId : NameEntryId(Handle);
        Entry.Header.Len = View.Len;

        Entry.StoreName(View.Name, View.Len);
        return Handle;
    }

    NameEntry& Resolve(NameEntryHandle Handle) const {
        return *(NameEntry*) (Blocks[Handle.Block] + Handle.Offset * alignof(NameEntry));
    }

private:
    friend class NamePool;
    
    void AllocateNewBlock() {
        ++CurrentBlock;
        Expects(CurrentBlock < MaxNumOfBlocks);
        CurrentBytesCursor = 0;

        if (Blocks[CurrentBlock] == nullptr) {
            Blocks[CurrentBlock] = AllocMemForBlock();
        }
    }

    uint8* AllocMemForBlock() {
        return (uint8*) (VMemory::Alloc(MaxNumOfOffsets * alignof(NameEntry)));
    }

    uint32 CurrentBlock = 0;
    uint32 CurrentBytesCursor = 0;
    uint8* Blocks[MaxNumOfBlocks] = {};
};

class NamePool {

public:
    static NamePool& GetNamePool() {
        static NamePool Pool;
        return Pool;
    }

    NameEntryId Store(NameView View);
    
    NameEntryId Find(NameView View);

    NameEntry& Resolve(NameEntryHandle Handle) {
        return Allocator.Resolve(Handle);
    }

private:
    
    NameEntryId FindOrCreateInternal(NameView View, bool bAdd,NameEntryId ComparisonId) {
        Expects(View.Name && View.Len > 0);

        NameHash Hash(View.Name,View.Len);

        for (uint32 block = 0; block <= Allocator.CurrentBlock; block++) {
            for (uint32 offset = 0; offset < MaxNumOfOffsets; offset++) {
                NameEntry& Entry = Resolve(NameEntryHandle(block, offset));

                if (!Hash.CompareFast(Entry.Header)) {
                    continue;
                }

                if (memcmp(Entry.Name,View.Name,View.Len) == 0) {
                    return Entry.CompareEntry;
                }
            }
        }

        if (!bAdd) {
            return NameEntryId();
        }

        NameEntryHandle Handle = Allocator.Create(View,ComparisonId);
        NameEntry& Entry = Resolve(Handle);
        Entry.Header.ProbHash = Hash.MinHash;

        return NameEntryId(Handle);
    }
    
    NameEntryAllocator Allocator;
};

class Name {
    friend struct NameHelper;
    
public:
    Name() = default;

    Name(Name Other, int32 InNumber)
        : Name(CreateNameInternal(Other.GetComparisonIndex(),InNumber)) {}

    Name(NameEntryId InComparisonIndex, NameEntryId InDisplayIndex, int32 InNumber)
        : Name(CreateNameInternal(InComparisonIndex, InDisplayIndex, InNumber)) {}

    Name(const  char* Name,EFindState FindState = FindState_Add);
    
    Name(const char* Name, int32 InLen, EFindState FindState = FindState_Add);

    Name(const char* Name,int32 InNumber);
    Name(const char* Name,int32 InLen,int32 InNumber);

    bool operator==(const Name& Other) const {
        return ComparisonIndex.ToInteger() == Other.ComparisonIndex.ToInteger() && Number == Other.Number;
    }
    
    NameEntryId GetComparisonIndex() {
        return ComparisonIndex;
    }

    NameEntryId GetDisplayIndex() {
        return DisplayIndex;
    }

    const NameEntry* GetComparisonEntry() const {
        return Resolve(ComparisonIndex);
    }

    const NameEntry* GetDisplayEntry() const {
        return Resolve(DisplayIndex);
    }

    int32 GetNumber() const {
        return Number;
    }

    NameEntry* Resolve(NameEntryId EntryId) const {
        return &NamePool::GetNamePool().Resolve(EntryId); // Soucis de retour de valeur locale ? 
    }

    std::string ToString() const;
    void ToString(std::string& OutStr) const;

    void AppendString(std::string& OutStr) const;

private:
    static Name CreateNameInternal(NameEntryId ComparisonId,NameEntryId DisplayId, int32 InNumber) {
        Name Out;

        Out.ComparisonIndex = ComparisonId;
        Out.DisplayIndex = DisplayId;
        Out.Number = InNumber;
        
        return Out;
    }

    static Name CreateNameInternal(NameEntryId ComparisonId,int32 InNumber) {
        return CreateNameInternal(ComparisonId,ComparisonId,InNumber);
    }
    
    NameEntryId ComparisonIndex;
    NameEntryId DisplayIndex;
    int32 Number;
};

struct NameHelper {

    static Name CreateDetectNumber(NameView View,EFindState FindState) {
        if (View.Len == 0) {
            return Name();
        }

        int32 Num = ParseNumber(View);
        return CreateInternal(View,FindState,Num);
    }
    
    static Name CreateWithNumber(NameView View,int32 Number, EFindState FindState) {
        if (View.Len == 0) {
            return Name();
        }

        return CreateInternal(View,FindState,Number);
    }

private:
    
    static int32 ParseNumber(NameView View) {
        int32 NumDigits = 0;

        for (const char* it = View.Name + View.Len - 1;
             it >= View.Name && *it >= '0' && *it <= '9';
             --it) {
            ++NumDigits;
        }

        if (NumDigits == 0 || NumDigits >= View.Len) {
            return 0;
        }

        const char* FirstDigit = View.Name + View.Len - NumDigits;
        if (*(FirstDigit - 1) == '_') { // Probablement pas bon car prend juste le premier chiffre ? 
            return static_cast<int32>(_atoi64(FirstDigit));
        }

        return 0;
    }

    static Name CreateInternal(NameView View, EFindState FindState, int32 Number) {
        NameEntryIds IDs = FindOrStoreString(View, FindState);
        
        return Finalize(IDs,Number);
    }

    static Name Finalize(NameEntryIds EntryIds, int32 InNumber) {
        Name Out;

        Out.ComparisonIndex = EntryIds.Comparison;
        Out.DisplayIndex = EntryIds.Display;
        Out.Number = InNumber;

        return Out;
    }

    // Find the stored name associated to the display named
    static NameEntryId ResolveComparisonId(NameEntryId DisplayId) {
        if (!DisplayId.IsValid()) {
            return NameEntryId();
        }

        return NamePool::GetNamePool().Resolve(DisplayId).CompareEntry;
    }

    static NameEntryIds FindOrStoreString(NameView View, EFindState FindState) {
        NameEntryIds Result = {};
        
        NamePool& Pool = NamePool::GetNamePool();

        if (FindState == FindState_Add) {
            NameEntryId DisplayId = Pool.Store(View);
            Result = { ResolveComparisonId(DisplayId),DisplayId};
        } else {
            Expects(FindState == FindState_Find);
            NameEntryId DisplayId = Pool.Find(View);
            Result = { ResolveComparisonId(DisplayId),DisplayId};
        }

        return Result; 
    }
};

// Remove after chaning std::unordered_map to custom map
namespace std {
    template<>
    struct hash<Name> {
        size_t operator()(const Name& HName) const noexcept {
            uint64 Hash =(uint64(HName.GetComparisonEntry()->CompareEntry.ToInteger()) << 32) | uint64(HName.GetNumber());
            return std::hash<uint64>{}(Hash);
        }  
    };
}
